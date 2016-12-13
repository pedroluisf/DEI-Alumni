<?php

function __autoload($classname) {
  $separator = ';';
  $docroot = $_SERVER['DOCUMENT_ROOT'];
  ini_set('include_path', ini_get('include_path') . $separator . $docroot . '/includes');
  
  require_once $classname . '.class.php';
}

?>
