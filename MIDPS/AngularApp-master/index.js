var express = require('express');
var app = express();
var mongoose = require('mongoose');
var config = require('./config');
var User = require('./app/models/User');
var setup = require('./app/routes/setup');
var login = require('./app/routes/login');
var todos = require('./app/routes/todos');
var bodyParser  = require('body-parser');

app.set('port', (process.env.PORT || 80));
mongoose.connect(config.database);


app.use(express.static(__dirname + '/public'));
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());



app.use('/api/v1/users', setup);
app.use('/api/v1/login', login);
app.use('/api/v1/todos', todos);



// views is directory for all template files
app.set('views', __dirname + '/views');
app.set('view engine', 'html');



app.listen(app.get('port'), function() {
  console.log('Node app is running on port', app.get('port'));
});


