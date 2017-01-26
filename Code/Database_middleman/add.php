<?php
   	include("connect.php");
   	
   	$link=Connection();

   $log_id=$_POST["log_id"];
   $time_date=$_POST["time_date"];
	$verified_as_crash=$_POST["verified_as_crash"];
	$cam_id=$_POST["cam_id"];
   $location=$_POST["location"];
   $video_link=$_POST["video_link"];

	$query = "INSERT INTO `logs` (`log_id`, `time_date`, `verified_as_crash`, `cam_id`, `location`, `video_link`) 
		VALUES ('".$log_id."','".$time_date."','".$verified_as_crash."','".$cam_id."','".$location."','".$video_link."')"; 
   	
   	mysql_query($query,$link);
	mysql_close($link);

   	header("Location: index.php");
?>
