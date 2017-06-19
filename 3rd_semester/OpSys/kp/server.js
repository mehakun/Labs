const net = require('net');
const fs = require('fs');
const Heap = require('heap');
const Message = require('./message');
const SETTINGS_FILE = './settings.json';
const MAP_FILE = './journal/queues.json';
const settings = JSON.parse(fs.readFileSync(SETTINGS_FILE, 'utf-8'));
let mapFromFile = null;
try {
  mapFromFile = JSON.parse(fs.readFileSync(MAP_FILE, 'utf-8'));
} catch (err) {
  console.log('error while opening map');
}
const io = require('socket.io')(settings.port);
const jsonToMap = (jsonStr) => {
  return new Map(JSON.parse(jsonStr));
}
const save = (obj, filename, dateOn) => {
  fs.writeFile(`${settings.journalPath}/${filename}${(dateOn) ? Date.now() : ''}.json`, JSON.stringify(obj, null, 2), 'utf-8',
               (err) => {
                 if (err) {
                   console.error('smth wrong with writeFile', err);
                   throw err;
                 }
               });
};
let map = new Map();
let journalMap = new Map();
if (mapFromFile) {
  for (const maps of mapFromFile) {
    let queue = new Heap((a, b) => {
      return a.priority - b.priority;
    });
    
    for (const node of maps[1].nodes) {
      queue.push(node);
    }
    
    map.set(maps[0], queue);
  }
}

io.on('connection', (socket) => {
  let journalMode = false;
  let journalQueue = [];
  let queue = null;
  let currentId = -1;
  console.log(`USER CONNECTED:${socket.id}`);
  
  socket.on('create_queue', (id, err) => {
    if (map.has(id)) {
      err({id: id, msg: 'queue_exist'});
    } else {
      const res = map.set(id, new Heap((a, b) => {
        return a.priority - b.priority;
      }));
      
      if (res) {
        err({id: id, msg: 'queue_created'});
      } else {
        err({id: id, msg: 'queue_error'});
      }
    }
  });
  
  socket.on('delete_queue', (id, err) => {
    if (map.delete(id)) {
      if (currentId === id) {
        queue = null;
        journalMode = false;
      }
      journalMap.delete(id);
      err({id: id, msg: 'queue_delete'});
    } else {
      err({id: id, msg: 'queue_null'});
    }    
  });
  
  socket.on('connect_to_queue', (id, err) => {
    queue = map.get(id);
    if (queue) {
      journalMode = false;
      currentId = id;
      err({id: id, msg: 'queue_connected'});
    } else {
      err({id: id, msg: 'queue_null'});
    }
  });
  
  socket.on('push', (obj, err) => {
    if (map.has(currentId)) {
      queue = map.get(currentId);
      if (journalMode) {
        journalQueue = journalMap.get(currentId);
        journalQueue.push(obj);
        journalMap.set(currentId, journalQueue);
      }
      
      queue.push(obj);
      if (map.set(currentId, queue)) {
        err({answer: 'OK', msg: null});
      } else {
        err({answer: 'FAIL', msg: null});
      }
    } else {
      err({answer: 'null', msg: null});
    }
  });

  socket.on('pop', (err) => {
    if (map.has(currentId)) {
      queue = map.get(currentId);
      if (!queue.empty()) {
        if (journalMode) {
          // do smth when pop
        }
        const msg = queue.pop();
        if (map.set(currentId, queue) && msg) {
          console.log(`popped ${msg}`);
          err({answer: 'OK', msg: msg});
        } else {
          err({answer: 'FAIL', msg: null});
        }
      } else {
        console.log('empty queue');
        err({answer: 'FAIL', msg: null});
      }
    } else {
      err({answer: 'null', msg: null});
    }
  });

  socket.on('top', (err) => {
    if (map.has(currentId)) {
      queue = map.get(currentId);
      if (!queue.empty()) {
        const msg = queue.peek();
        console.log(`peeked ${JSON.parse(msg)}`);
        err({answer: 'OK', msg: msg});
      } else {
        console.log('empty queue');
        err({answer: 'FAIL', msg: null});
      }
    } else {
      err({answer: 'null', msg: null});
    }
  });  

  socket.on('journal_curr_q', (mode, err) => {
    journalMode = mode;
    if (journalMode) {
      if (journalMap.has(currentId)) {
        journalQueue = journalMap.get(currentId);
      } else {
        journalMap.set(currentId, []);
        journalQueue = journalMap.get(currentId);
      }
    }
    err({msg: 'OK', id: currentId});
  });

  socket.on('show_journal', (err) => {
    const tmp = journalMap.get(currentId);
    
    if (tmp && tmp.length) {
      console.log('showing journal', tmp);
      err({msg: 'OK', q: tmp.slice()});
    } else {
      console.log('empty journal or error');
      err({msg: 'FAIL', q: null});
    }
  });
  
  socket.on('disconnect', (reason) => {
    console.log(`Disconnect:${reason}`);
  });  
  
});

process.on('SIGINT', () => {
  console.log('\nsaving queues');
  save([...map], 'queues', false);
  console.log('closing server');
  io.close(() => {
    console.log('every connection is closed');
  });
}).on('SIGTERM', () => {
  console.log('\nsaving queues');
  save([...map], 'queues', false);
  console.log('closing server');
  io.close(() => {
    console.log('every connection is closed');
  });
});
