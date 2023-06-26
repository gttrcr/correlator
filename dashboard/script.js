function openTab(evt, cityName) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(cityName).style.display = "block";
    evt.currentTarget.className += " active";
}


function loadPages(json) {
    //print loaded json
    console.log(json);

    //popolate arguments table
    var table = document.getElementById("arguments_table");
    for (var key in json.args) {
        var row = table.insertRow();
        var c1 = row.insertCell(); // argument name
        var c2 = row.insertCell(); // value
        c1.innerHTML = key;
        c2.innerHTML = json.args[key];
        table.appendChild(row);
    }

    //popolate dataset table
    var table = document.getElementById("dataset_table");
    for (var i = 0; i < json.csv_files.length; i++) {
        var row = table.insertRow();
        var c1 = row.insertCell(); // file name
        var c2 = row.insertCell(); // number of rows
        var c3 = row.insertCell(); // number of columns
        c1.innerHTML = json.csv_files[i]["filename"];
        c2.innerHTML = json.csv_files[i]["number_of_rows"];
        c3.innerHTML = json.csv_files[i]["number_of_columns"];
        table.appendChild(row);
    }
}

var openFile = function (event) {
    var input = event.target;
    var reader = new FileReader();
    var text = reader.readAsText(input.files[0]);
    reader.onload = function () {
        var text = reader.result;
        var jsonResult = JSON.parse(text);
        loadPages(jsonResult);
    };
};