<?php

    require_once "dbDetails.php";

    $conn = mysqli_connect(HOST, USER, PASS);

    mysqli_set_charset($conn, "utf8");
    mysqli_select_db($conn, DB);

    if(mysqli_connect_errno()){
        echo "connect fail";
    }
    $today = date("Y-m-d");
    
    $data_stream = "'".$_POST['email']."','".$_POST['name']."','".$today."'";

    $query = "insert into login( email, name, signdate) values (".$data_stream.")";
    
    echo $query;

    $result = mysqli_query($conn, $query);

    if($result)
    echo "1";
    else
    echo "-1";

    mysqli_close($conn);

?>