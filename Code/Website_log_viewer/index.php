<?php

ini_set('display_errors','On');
error_reporting(E_ALL);

function display_debug($key, $value, $debug=false) {
  if($debug){
    echo ''.$key . " = ";
    switch (gettype($value)) {
      case 'string' :
        echo $value;
        break;
      case 'array' :
      case 'object' :
      default :
        echo '';
        print_r($value);
        echo ''; 
        break;
} } }

$db_host = 'localhost'; // Server Name
$db_user = 'root'; // Username
$db_pass = '63AyvMSZec'; // Password
$db_name = 'grupp4'; // Database Name

$conn = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
if (!$conn) {
	die ('Failed to connect to MySQL: ' . mysqli_connect_error());	
}

$sql = 'SELECT * 
		FROM logs
        ORDER BY log_id DESC';
		
$query = mysqli_query($conn, $sql);

if (!$query) {
	die ('SQL Error: ' . mysqli_error($conn));
}

$test = 0;
$arrayVals = array();
while ($row = mysqli_fetch_array($query)){
    $arrayVals[] = $row;
}

if(isset($_GET['update']))
{
    $value = $_GET['update'];
    $id = $_GET['info'];
    
   
    display_debug('Value: ',$test, 1);
    $test = $test +1;
    //display_debug('<br> ID: ',$id, 1);
    
    $a= "UPDATE logs SET verified_as_crash='$value' WHERE log_id=$id";
    $b = mysqli_query($conn, $a);
    
    if (!$b) {
	   die ('SQL Error: ' . mysqli_error($conn));
    }
    
   
    mysqli_close($conn);
    //echo "<meta http-equiv='refresh' content='0'>";
    header("Location: http://188.166.72.14/index.php?caller=somevalue");
    //header('Location: '.$_SERVER['REQUEST_URI']);
    //$value = $_POST['name'];
    //$id = $_POST['id'];
    
    
}    

if( isset( $_GET["caller"] ) && $_GET["caller"] == "somevalue" ) {
    // I'm using Location because this will remove the get value
    header( "Location: index.php" );
    exit;
}
?>



<html>
<head>
	<title>Q6115-E Crash Data</title>
	<style type="text/css">
		body {
			font-size: 15px;
			color: #343d44;
			font-family: "segoe-ui", "open-sans", tahoma, arial;
			padding: 0;
			margin: 0;
		}
		table {
			margin: auto;
			font-family: "Lucida Sans Unicode", "Lucida Grande", "Segoe Ui";
			font-size: 12px;
		}

		h1 {
			margin: 25px auto 0;
			text-align: center;
			text-transform: uppercase;
			font-size: 17px;
		}

		table td {
			transition: all .5s;
		}
		
		/* Table */
		.data-table {
			border-collapse: collapse;
			font-size: 14px;
			min-width: 537px;
		}

		.data-table th, 
		.data-table td {
			border: 1px solid #e1edff;
			padding: 7px 17px;
		}
		.data-table caption {
			margin: 7px;
		}

		/* Table Header */
		.data-table thead th {
			background-color: #508abb;
			color: #FFFFFF;
			border-color: #6ea1cc !important;
			text-transform: uppercase;
		}

		/* Table Body */
		.data-table tbody td {
			color: #353535;
		}
		.data-table tbody td:first-child,
		.data-table tbody td:nth-child(4),
		.data-table tbody td:last-child {
			text-align: right;
		}

		.data-table tbody tr:nth-child(odd) td {
			background-color: #f4fbff;
		}
		.data-table tbody tr:hover td {
			background-color: #ffffa2;
			border-color: #ffff0f;
		}

		/* Table Footer */
		.data-table tfoot th {
			background-color: #e5f5ff;
			text-align: right;
		}
		.data-table tfoot th:first-child {
			text-align: left;
		}
		.data-table tbody td:empty
		{
			background-color: #ffcccc;
		}
        
        /* Style the tab */
        div.tab {
            overflow: hidden;
            border: 1px solid #ccc;
            background-color: #fff;
        }

        /* Style the links inside the tab */
        div.tab a {
            float: left;
            display: block;
            color: black;
            text-align: center;
            padding: 14px 16px;
            text-decoration: none;
            transition: 0.3s;
            font-size: 17px;
        }

        /* Change background color of links on hover */
        div.tab a:hover {
            background-color: #f4fbff;
        }

        /* Create an active/current tablink class */
        div.tab a:focus, .active {
            background-color: #508abb;
        }

        /* Style the tab content */
        .tabcontent {
            display: none;
            padding: 6px 12px;
            border: 1px solid #ccc;
            border-top: none;
        }
	</style>
</head>
<body>
    
<script>
    document.addEventListener('DOMContentLoaded',function(){
        document.getElementById("defaultOpen").click();
    });
</script>
    
    <script>
        
        function openTab(evt, tabName) {
            // Declare all variables
            var i, tabcontent, tablinks;

            // Get all elements with class="tabcontent" and hide them
            tabcontent = document.getElementsByClassName("tabcontent");
            for (i = 0; i < tabcontent.length; i++) {
                tabcontent[i].style.display = "none";
            }

            // Get all elements with class="tablinks" and remove the class "active"
            tablinks = document.getElementsByClassName("tablinks");
            for (i = 0; i < tablinks.length; i++) {
                tablinks[i].className = tablinks[i].className.replace(" active", "");
            }

            // Show the current tab, and add an "active" class to the link that opened the tab
            document.getElementById(tabName).style.display = "block";
            evt.currentTarget.className += " active";
        } 
        
       // document.getElementById("defaultOpen").click();
        
    </script>
    
	<h1>Q6115-E DATABASE FOR REGISTERED CRASH EVENTS</h1>
    
    <div class="tab">
    
        <a href="javascript:void(0)" class="tablinks" onclick="openTab(event, 'UNVERIFIED')" id="defaultOpen" >UNVERIFIED</a>
        
        <a href="javascript:void(0)" class="tablinks" onclick="openTab(event, 'LOGS')" >LOGS</a>
    
    </div>
    
    <div id="UNVERIFIED" class="tabcontent">
	<table class="data-table">
		<caption class="title">UNVERIFIED CRASH DATA</caption>
		<thead>
			<tr>
				<th>NO</th>
				<th>VIDEO LINK</th>
                <th>IMAGE LINK</th>
				<th>LOCATION</th>
				<th>DATE</th>
				<th>STATUS</th>
                <th>CAMERA ID</th>
                <th>REPORT INCIDENT</th>
			</tr>
		</thead>
		<tbody>
		<?php

            $len = count($arrayVals);
            for($x = 0; $x < $len; $x++){
                $row = $arrayVals[$x];
                
                if($row['verified_as_crash']=='UNVERIFIED'){
                    
                    echo 
                        '<tr>
                            <td>'.$row['log_id'].'</td>
				            <td><video width="320" height="180" controls src="'.$row['video_link'].'"></video></td>
                            <td><a href="'.$row['img_link'].'"><img height="180" width="320" src="'.$row['img_link'].'"></a></td>
				            <td><a href="http://maps.google.com/maps?q='.$row['location'].'">Location</a></td>
				            <td>'.$row['time_date'] . '</td>
                            <td>'.$row['verified_as_crash'].'</td>
                            <td>'.$row['cam_id'].'</td>
                            <td> ';?>     
                        
                            <form method="get" action="<?php $_PHP_SELF ?> ">
                                
                                <input  name  = "info" 
                                        type  = "hidden" 
                                        id    = "1" 
                                        value = "<?php echo $row['log_id']; ?>"/>
                                
                                <input  name  = "update" 
                                        type  = "submit" 
                                        id    = "15" 
                                        value = "POSITIVE"/>
                                
                                <input  name  = "update" 
                                        type  = "submit" 
                                        id    = "15" 
                                        value = "NEGATIVE"/>
                            </form>
                            
                            <?php
                            
                            '</td>
                        </tr>';
                }
            }
        ?>
            
		</tbody>
	</table>
    
    </div>
    
    <div id="LOGS" class="tabcontent">
	<table class="data-table">
		<caption class="title">CRASH DATA LOGS</caption>
		<thead>
			<tr>
				<th>NO</th>
				<th>VIDEO LINK</th>
                <th>IMAGE LINK</th>
				<th>LOCATION</th>
				<th>DATE</th>
				<th>STATUS</th>
                <th>CAMERA ID</th>
			</tr>
		</thead>
		<tbody>
		<?php

            $len = count($arrayVals);
            for($x = 0; $x < $len; $x++){
                $row = $arrayVals[$x];
                
                if($row['verified_as_crash']!='UNVERIFIED'){
                    echo 
                    
                    '<tr>
                        <td>'.$row['log_id'].'</td>
				        <td><video width="320" height="180" controls src="'.$row['video_link'].'"></video></td>
                        <td><img height="180" width="320" src="'.$row['img_link'].'"></td>
				        <td><a href="http://maps.google.com/maps?q='.$row['location'].'">Location</a></td>
				        <td>'.$row['time_date'] . '</td>
				        <td>'.$row['verified_as_crash'].'</td>
                        <td>'.$row['cam_id'].'</td>
				    </tr>';
                }
            }
        ?>
            
		</tbody>
	</table>
    </div>
</body>
</html>