<?php

/**
 * Description of Logger
 *
 * @author Pedro
 */
class Logger {

  private static $fileName = 'log.txt';

  public static function log($message) {
    $date = new DateTime();
    $logLine = $date->format('Y-m-d H:i:s') . ' >> ' . $message . "\n";

    $f = fopen(self::$fileName, 'a');
    fwrite($f, $logLine);
    fclose($f);
  }

  public static function logException(Exception $e) {
    $date = new DateTime();
    $logLine = $date->format('Y-m-d H:i:s') . ' >> ' . $e->getMessage() . "\n" . $e->getTraceAsString() . "\n";

    $f = fopen(self::$fileName, 'a');
    fwrite($f, $logLine);
    fclose($f);
  }

}

?>
