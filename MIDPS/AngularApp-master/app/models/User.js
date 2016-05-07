/**
 * Created by lschidu on 4/26/16.
 */

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

module.exports = mongoose.model('User', new Schema({
    name: String,
    password: String
}));