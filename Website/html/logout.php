<?php

session_start();

unset($_SESSION["DEI_user"]);
unset($_SESSION["DEI_msg"]);
unset($_SESSION["DEI_Lang"]);
session_destroy();

header('Location:/index.php');

?>
