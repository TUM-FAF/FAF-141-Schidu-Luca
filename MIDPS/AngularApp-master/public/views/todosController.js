/**
 * Created by lschidu on 4/27/16.
 */
(function() {

    angular.module('MainModule').controller('todosController', controller);

    function controller($http, $window, $scope) {
        var vm = this;
        vm.todos;
        vm.buttonName = "Add";
        vm.addTodo = addTodo;
        vm.todoObject = {};
        vm.addTodo = addTodo;
        vm.updateTodo = updateTodo;
        vm.removeTodo = removeTodo;
        vm.logout = logout;
        vm.changeRoute = changeRoute;
        vm.changeButtonAdd = changeButtonAdd;
        vm.changeButtonUpdate = changeButtonUpdate;
        vm.completeFormFields = completeFormFields;
        vm.performAction = performAction;
        vm.request = request;
        
        vm.request();
        
        function request() {

            $http.get('/api/v1/todos?token='+ $window.sessionStorage.token + "&userId=" + $window.sessionStorage.userId).then(function(response) {
                if(response.data.message === "Failed to authenticate token") {
                    vm.changeRoute('#/');
                }else{
                    vm.todos = response.data;
                }
            });
        }


        function changeButtonAdd() {
            vm.buttonName = "Add";
        }

        function changeButtonUpdate() {
            vm.buttonName = "Update";
        }
        
        
        function completeFormFields(index) {
            vm.todoObject.title = vm.todos[index].title;
            vm.todoObject.priority = vm.todos[index].priority;
            vm.todoObject.postDate = vm.todos[index].postDate;
            vm.todoObject.deadline = vm.todos[index].deadline;
            vm.todoObject._id = vm.todos[index]._id;
        }
        
        
        function addTodo() {

            vm.todoObject.userId = $window.sessionStorage.userId;

            $http.post('/api/v1/todos/add', vm.todoObject).success(function(data) {
                console.log( "log " + data);

            }).error(function(data) {
                console.log('Error: ' + data);
            });

            $http.get('/api/v1/todos?token='+ $window.sessionStorage.token + "&userId=" + $window.sessionStorage.userId).then(function(response) {
                vm.todos = response.data;
            });

            vm.todoObject = {};
        }


        function performAction(index) {
            if(vm.buttonName === "Add") {
                addTodo();
            }else {
                updateTodo(index);
            }
        }

        function removeTodo(index) {

            $http.post('/api/v1/todos/remove', vm.todos[index]).success(function(data) {
                console.log( "log " + data);

            }).error(function(data) {
                console.log('Error: ' + data);
            });

            vm.todos.splice(index, 1);
        }



        function updateTodo() {

            $http.post('/api/v1/todos/update', vm.todoObject).success(function(data) {
                console.log( "log " + data);
            }).error(function(data) {
                console.log('Error: ' + data);
            });

                $http.get('/api/v1/todos?token='+ $window.sessionStorage.token + "&userId=" + $window.sessionStorage.userId).then(function(response) {
                vm.todos = response.data;
            });
            
        }


        function logout() {
            $window.sessionStorage.token = null;
            vm.changeRoute('#/');
        }


        function changeRoute(url, forceReload) {
            $scope = $scope || angular.element(document).scope();
            if(forceReload || $scope.$$phase) {
                window.location = url;
            } else {
                $location.path(url);
                $scope.$apply();
            }
        }
    }

})();