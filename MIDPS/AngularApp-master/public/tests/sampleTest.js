/**
 * Created by lschidu on 5/3/16.
 */
describe('Controller : todosController', function() {

    beforeEach(module('MainModule'));


    var controller;
    var scope;

    beforeEach(inject(function($controller, $rootScope) {
        scope = $rootScope.$new();
        controller = $controller('todosController' , {
            $scope: scope
        });


    }));

    describe('it should pass', function() {

        it('sampleTest', function() {
            expect(controller.buttonName).toBe("Add");
        });

        it('Should change button name', function() {
            controller.changeButtonUpdate();
            expect(controller.buttonName).toBe("Update");
        });



        it('Should delete a row ', function() {
            controller.request();
            expect(controller.todos).toBeUndefined(true);
        });

    });


    var location;
    var route;
    var rootScope;

    beforeEach(inject(function($location, $rootScope, $route) {
        location = $location;
        rootScope = $rootScope;
        route = $route;
    }));

});