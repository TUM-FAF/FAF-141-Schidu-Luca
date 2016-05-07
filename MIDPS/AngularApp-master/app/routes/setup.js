/**
 * Created by lschidu on 4/26/16.
 */

var express = require('express');
var router = express.Router();
var User = require('../models/User');
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

    User.find({}, function(err, users) {
        res.json(users);
    });
});




module.exports = router;
