/**
 * Created by lschidu on 4/27/16.
 */

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

module.exports = mongoose.model('todo', new Schema({
    title: String,
    priority: String,
    postDate : String,
    deadline : String,
    userId : String
}));
