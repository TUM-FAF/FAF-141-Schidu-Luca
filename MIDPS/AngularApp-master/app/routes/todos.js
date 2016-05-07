/**
 * Created by lschidu on 4/27/16.
 */
/**
 * Created by lschidu on 4/26/16.
 */

var express = require('express');
var router = express.Router();
var Todo = require('../models/Todo');
var jwt = require('jsonwebtoken');
var config = require('../../config');



function checkToken(req, res, next) {
    var token = req.body.token || req.query.token || req.headers['x-access-token'];

    if(token) {

        jwt.verify(token, config.secret, function(error, decoded) {
            if(error) {
                return res.json({message : "Failed to authenticate token"});
            }else {
                req.decoded = decoded;
                next();
            }
        });

    } else {
        return res.status(403).send({
            success: false,
            message: 'No token provided.'
        });
    }
}


router.get('/', checkToken, function (req, res, next) {
    
    Todo.find({'userId' : req.query.userId}, function(err, users) {
        res.json(users);
    });
});



router.post('/add', function(req, res, next) {

    var todo = new Todo({
        title: req.body.title,
        priority: req.body.priority,
        postDate: req.body.postDate,
        deadline : req.body.deadline,
        userId : req.body.userId
    });

    todo.save(function(error) {
        if(error)  throw  error;
    });

});



router.post('/update', function(req, res, next) {


    Todo.find({_id : req.body._id}, function(err, todo) {

        var model = todo[0];
        console.log(req.body._id);
        model.title = req.body.title;
        model.postDate = req.body.postDate;
        model.deadline = req.body.deadline;
        model.priority = req.body.priority;

        model.save(function(error) {
            if(error)  throw  error;
        });

    });

});




router.post('/remove', function(req, res, next) {
    Todo.remove({_id : req.body._id}, function(err) {
        if(err) {
            console.log(err);
        }
    });
});



module.exports = router;
