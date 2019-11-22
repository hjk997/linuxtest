<?php
    
    require_once "dbDetails.php";

    $conn = mysqli_connect(HOST, USER, PASS);

    if(mysqli_connect_errno()){
        echo "connect fail";
    }
    
    mysqli_set_charset($conn, "utf8");
    mysqli_select_db($conn, DB);
        
    //$userID = $_post['userId'];
    $query = "SELECT * FROM login;";

    //연결된 데이터베이스에 위에서 작성한 쿼리를 전송하고 그 결과값을 result 변수에 저장
    //실제로 쿼리 날림
    $res = mysqli_query($conn, $query);

    //array() 형식 객체 2개 생성 ( object 형식은 적합하지 않기 때문 )
    $rows = array();
    $result = array();


    while($row = mysqli_fetch_array($res)){
        //$row["필요한 ID - 안드로이드에서 JSON 파싱할 때 사용할 태그"]
        $rows["id"] = $row[0];
        $rows["email"] = $row[1];
        $rows["name"] = $row[2];
        $rows["signdate"] = $row[3];
        
        //$rows에 들어간 데이터들을 $result 배열에 ADD
        array_push($result, $rows);
        //die("success"); //특정 문자 넣으면서 프로그램을 종료
    }
    echo json_encode(array("results"=>$result));

    mysqli_close($conn);

?>