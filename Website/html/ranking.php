<?php

session_start();

ini_set('include_path', ini_get('include_path') . ':../includes');
require_once 'Page.class.php';
require_once 'Global.php';

if (isset($_GET['lang'])){
	$lang = 'pt';
	if ($_GET['lang'] == 'pt') $lang = 'pt';
	if ($_GET['lang'] == 'en') $lang = 'en';
	$_SESSION["DEI_Lang"] = $lang;
} elseif (isset($_SESSION["DEI_Lang"])){
	$lang = $_SESSION["DEI_Lang"];
} else {
	$lang = 'pt';
	$_SESSION["DEI_Lang"] = $lang;
}

if (isset($_SESSION["DEI_user"]))
	$p = new Page('ranking.html.php', 'DEI Alumni', $lang);
else
	$p = new Page('ranking_not_allowed.html.php', 'DEI Alumni', $lang);
$p->setActiveMenu(2);
$p->show();

?>