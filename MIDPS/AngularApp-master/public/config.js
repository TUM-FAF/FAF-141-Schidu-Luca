/**
 * Created by lschidu on 4/27/16.
 */

(function() {

    angular.module('MainModule').config(['$routeProvider',
        function($routeProvider) {
            $routeProvider.
            when('/', {
                templateUrl: 'views/login-view.html',
                controller: 'loginViewController',
                controllerAs: 'vm'
            }).
            when('/todos', {
                templateUrl: 'views/todos.html',
                controller: 'todosController'
            }).
            otherwise({
                redirectTo: '/'
            });
        }]);
    
    
    
})();