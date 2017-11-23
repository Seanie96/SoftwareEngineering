        $("#submit").click(function(){
                 console.log("here boi");
                 var name = document.getElementById("persons_username");
                 var act_name = name.value;
                 console.log(act_name);
                 $.ajax({url: "/username",
                         type: "POST",
                         dataType: "json",
                         data: { user: act_name },
                         success: function(result){
                                 console.log("made it this far");
                                 var tbl = document.createElement('table');
                                 var user_name_row = document.createElement('tr');
                                 var user_name = document.createElement('td');
                                 var user_name_name = document.createElement('td');
                                 var bio_row = document.createElement('tr');
                                 var bio = document.createElement('td');
                                 var bio_bio = document.createElement('td');
                                 var num_of_repos_row = document.createElement('tr');
                                 var num_of_repos = document.createElement('td');
                                 var num_of_repos_repos = document.createElement('td');
                                 var repos_data_row = document.createElement('tr');
                                 var repos_data = document.createElement('td');
                                 var repos_dat_data = document.createElement('td');
                                 var arr_of_repos = [];
                                 result.repoInformation.forEach(function(element) {
                                        console.log(element);
                                 });
                                 $("#tables_of_data").append(result);
              }});
         });
