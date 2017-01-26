<?php

	include("connect.php"); 	
	
	$link=Connection();

	$result=mysql_query("SELECT * FROM `logs` ORDER BY `log_id` DESC",$link);
?>

<html>
   <head>
      <title>Logs</title>
   </head>
<body>
   <h1>Logs</h1>

   <table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;log id&nbsp;</td>
			<td>&nbsp;time date&nbsp;</td>
			<td>&nbsp;verified&nbsp;</td>
			<td>&nbsp;cam id&nbsp;</td>
			<td>&nbsp;location&nbsp;</td>
			<td>&nbsp;video link&nbsp;</td>
		</tr>

      <?php 
		  if($result!==FALSE){
		     while($row = mysql_fetch_array($result)) {
		        printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td></tr>", 
		           $row["log_id"], $row["time_date"], $row["verified_as_crash"], $row["cam_id"], $row["location"], $row["video_link"]);
		     }
		     mysql_free_result($result);
		     mysql_close();
		  }
      ?>

   </table>
</body>
</html>
