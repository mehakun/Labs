const fs = require('fs');
const readline = require('readline');
const Message = require('./message');
const SETTINGS_FILE = './settings.json';
const settings = JSON.parse(fs.readFileSync(SETTINGS_FILE, 'utf-8'));
console.log(`server address is: ${settings.host}:${settings.port}`);
const client = require('socket.io-client')(`${settings.host}:${settings.port}`);
let id = 1;
let ans = null;
const completerFunc = (line) => {
  const completions = 'create_queue delete_queue connect_to_queue push pop top journal_curr_q show_journal'.split(' ');
  const hits = completions.filter((c) => { return c.indexOf(line) === 0 });
  return [hits.length ? hits : completions, line];
};
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  completer: completerFunc,
  prompt: 'commands:\ncreate_queue ID\ndelete_queue ID\nconnect_to_queue ID\npush Text Priority\npop\\top\njournal_curr_q on\\off\nshow_journal\n'
});

client.on('connect', (obj) => {
  console.log('CONNECTED TO: ' + settings.host + ':' + settings.port);
  rl.prompt();
  rl.on('line', (line) => {
    const args = line.split(' ');
    switch (args.length) {
    case 1:
      switch (args[0]) {
      case 'pop':
        client.emit('pop', (err) => {
          if (err.answer === 'OK') {
            console.log('got msg', err.msg);
            ans = err.msg;
          } else if (err.answer === 'FAIL') {
            console.log('queue is empty or something');
          } else {
            console.log('connect to queue!');
          }
        });
        break;
      case 'top':
        client.emit('top', (err) => {
          if (err.answer === 'OK') {
            console.log('got msg', err.msg);
            ans = err.msg;
          } else if (err.answer === 'FAIL') {
            console.log('queue is empty or something');
          } else {
            console.log('connect to queue!');
          }
        });
        break;
      case 'show_journal':
        client.emit('show_journal', (err) => {
          if (err.msg === 'OK') {
            console.log('got journal ', err.q);
          } else {
            console.log('journal is empty or idk');
          }
        })
        break;
      }
      break;
    case 2:
      const queueId = parseInt(args[1]);
      if ((isNaN(queueId) || queueId < 0) && args[1] !== 'on' && args[1] !== 'off') {
        console.log('wrong id');
      } else {
        switch(args[0]) {
        case 'create_queue':
          client.emit('create_queue', queueId, (err) => {
            if (err.msg === 'queue_exist') {
              console.log(`queue with id ${err.id} exists`);
            } else if (err.msg === 'queue_created') {
              console.log(`queue with id ${err.id} created`);
            } else {
              console.log('some error');
            }
          });
          break;
        case 'delete_queue':
          client.emit('delete_queue', queueId, (err) => {
            if (err.msg === 'queue_delete') {
              console.log(`queue with id ${err.id} deleted`);
            } else if (err.msg === 'queue_null') {
              console.log(`queue with id ${err.id} doesnt exist`);
            } else {
              console.log('some error');
            }
          });
          break;
        case 'connect_to_queue':
          client.emit('connect_to_queue', queueId, (err) => {
            if (err.msg === 'queue_connected') {
              console.log(`connected to queue with id ${err.id}`);
            } else if (err.msg === 'queue_null') {
              console.log(`queue with id ${err.id} doesnt exist`);
            } else {
              console.log('some error');
            }
          });
          break;
        case 'journal_curr_q':
          if (args[1] === 'on') {
            client.emit('journal_curr_q', true, (err) => {
              if (err.msg === 'OK') {
                console.log(`journal mode is on for queue with id ${err.id}`);
              } else {
                console.log('some error');
              }
            });
          } else if (args[1] === 'off') {
            client.emit('journal_curr_q', false, (err) => {
              if (err.msg === 'OK') {
                console.log(`journal mode is off for queue with id ${err.id}`);
              } else {
                console.log('some error');
              }
            });            
          } else {
            console.log('meh');
          }
          break;
        }
      }
      break;
    default:
      if (args[0] === 'push') {
        const parseRes = parseInt(args[args.length - 1]);
        const priority = (isNaN(parseRes) || parseRes < 0) ? 10 : parseRes;
        id++;
        const ID = id;
        const text = args.slice(1, args.length - 1).join(' ');
        const msg = new Message(text, priority, ID);
        client.emit('push', JSON.stringify(msg), (response) => {
          if (response.answer === 'OK') {
            console.log('push went OK');
          } else if (response.answer === 'null') {
            console.log('connect to queue!');    
          } else {
            console.log('fail or error idc');
          }
        });
      } else {
        console.log('wrong');
      }
      break;
    }
  }).on('close', () => {
    console.log('EXITED');
    client.destroy();
    process.exit(0);
  });
});

client.on('error', (err) => {
  console.error('well', err);
});

client.on('disconnect', (err) => {
  console.log('Connection closed');
});
