<?php
   	include("connect.php");
   	
   	$link=Connection();

	$cam_id=$_POST["cam_id"];
    $location=$_POST["location"];
    $video_link=$_POST["video_link"];

	$query = "INSERT INTO `logs` ( `verified_as_crash`, `cam_id`, `location`, `video_link`) 
		VALUES ('UNVERIFIED','".$cam_id."','".$location."','".$video_link."')"; 
   	
   	mysql_query($query,$link);
	mysql_close($link);

    /*
      Send email to admin
      */
	// The message
$message = "A new car crash has possibly occurred.\r\n


Please verify by using the following resources: \r\n

Panorama picture: LINK HERE\r\n
Short video clip: LINK HERE\r\n
Live stream: LINK HERE\r\n
To verify the detection/view the log, go to: http://188.166.72.14\r\n


Have a nice day. :)\r\n
";

	// In case any of our lines are larger than 70 characters, we should use wordwrap()
	$message = wordwrap($message, 70, "\r\n");

	// Send
	mail('axisproject4@gmail.com', 'New crash possibly detected, please verify', $message);

   	header("Location: index.php");
?>
