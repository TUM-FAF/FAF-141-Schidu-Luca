/**
 * Created by lschidu on 4/27/16.
 */

(function() {

    angular.module('MainModule').controller('loginViewController', controller);


    function controller($http, $scope, $window) {

        var vm = this;
        vm.name = "";
        vm.password = "";
        vm.formData = {};
        vm.message = "";
        vm.login = login;
        vm.changeRoute = changeRoute;
        
        function login() {
            $http.post('/api/v1/login', vm.formData).success(function(data) {
                console.log(data);
                if(data.token != null) {
                    $window.sessionStorage.token = data.token;
                    $window.sessionStorage.userId = vm.formData.name;
                    vm.changeRoute('#/todos');
                    vm.message = "";
                }else {
                    vm.message = "Ups, try again";
                }
            }).error(function(data) {
                console.log('Error: ' + data);
            });
        }


        function changeRoute(url, forceReload) {
            $scope = $scope || angular.element(document).scope();
            if(forceReload || $scope.$$phase) {
                window.location = url;
            } else {
                $location.path(url);
                $scope.$apply();
            }
        };
    }

})();