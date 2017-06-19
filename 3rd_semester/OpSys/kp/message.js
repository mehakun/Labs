module.exports = class Message {
  constructor(text, priority, id) {
    this.text = text || '';
    this.priority = priority || 0;
    this.id = id || -1;
  }
}
