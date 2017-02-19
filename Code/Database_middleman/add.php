<?php
    /*
      Example usage:
      
      */

   	include("connect.php");
   	
   	$link=Connection();
    
    // Get information from Huzzah
	$cam_id=$_POST["cam_id"];
    $location=$_POST["location"];
    $video_link=$_POST["video_link"];
    
    $readdata = "SELECT MAX(log_id) FROM logs";
   	
    
	//mysql_close($link);
    
    //Create an index to link images to database
    $result = mysql_query($readdata,$link);
    $array = mysql_fetch_array($result);
    if(!$array[0]){
        $log_id_nr = 1;
    }else{
        $log_id_nr = $array[0] + 1;
    }
    
    // Add zeroes to filename to fit Axis numerical increments
    $log_id_nr = str_pad($log_id_nr, 5, '0', STR_PAD_LEFT);
    
    
    // Add strings for pathways to media
    $str_vid = "media/video/" . $log_id_nr . ".mkv";
    $str_img = "media/images/" . $log_id_nr . ".jpg";


	$query = "INSERT INTO `logs` ( `verified_as_crash`, `cam_id`, `location`, `video_link`, `img_link`) 
		VALUES ('UNVERIFIED','".$cam_id."','".$location."','".$str_vid."','".$str_img."')"; 

/*    $query = "INSERT INTO `logs` ( `verified_as_crash`, `cam_id`, `location`, `video_link`) 
		VALUES ('UNVERIFIED','".$cam_id."','".$location."','".$video_link."')"; 
*/   	
   	mysql_query($query,$link);
	mysql_close($link);



    /*
      Send email to admin
      */
	// The message
$message = "A new car crash has possibly occurred.\r\n


Please verify by using the following resources: \r\n

Image: http://188.166.72.14/".$str_img."
Video: http://188.166.72.14/".$str_vid."
Camera ID: ".$cam_id."
Location: http://maps.google.com/maps?q=".$location."
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
