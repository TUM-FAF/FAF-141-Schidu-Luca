/**
 * Created by lschidu on 5/3/16.
 */

describe('Testing the routes', function() {

    beforeEach(module('MainModule'));


    var location;
    var route;
    var rootScope;

    beforeEach(inject(function($location, $rootScope, $route) {
        location = $location;
        rootScope = $rootScope;
        route = $route;
    }));


    describe('route index', function() {

        beforeEach(inject(function($httpBackend) {

            $httpBackend.expectGET('public/views/login-view.html').
                respond(200, 'main HTML');
        }));

    });

});