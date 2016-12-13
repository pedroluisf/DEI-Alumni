<!DOCTYPE html>
<html lang="<?php echo $this->getLang(); ?>">
  <head>
    <title><?php echo $this->getTitle(); ?></title>
    <meta charset="utf-8">
    <link rel="stylesheet" href="css/reset.css" type="text/css" media="screen">
    <link rel="stylesheet" href="css/style.css" type="text/css" media="screen">
    <link rel="stylesheet" href="css/grid.css" type="text/css" media="screen">
    <script src="js/jquery-1.6.3.min.js" type="text/javascript"></script>
    <script src="js/cufon-yui.js" type="text/javascript"></script>
    <script src="js/cufon-replace.js" type="text/javascript"></script>
    <script src="js/Mate_400.font.js" type="text/javascript"></script>
    <script src="js/FF-cash.js" type="text/javascript"></script>
    <!--[if lt IE 7]>
    <div style=' clear: both; text-align:center; position: relative;'>
      <a href="http://windows.microsoft.com/en-US/internet-explorer/products/ie/home?ocid=ie6_countdown_bannercode">
        <img src="http://storage.ie6countdown.com/assets/100/images/banners/warning_bar_0000_us.jpg" border="0" height="42" width="820" alt="You are using an outdated browser. For a faster, safer browsing experience, upgrade for free today." />
      </a>
    </div>
    <![endif]-->
    <!--[if lt IE 9]>
      <script type="text/javascript" src="js/html5.js"></script>
      <link rel="stylesheet" href="css/ie.css" type="text/css" media="screen">
    <![endif]-->
  </head>
  <body id="page5">
    <div class="extra">
      <div class="main">
        <!--==============================header=================================-->
        <header>
          <?php require_once 'menu.inc.php'; ?>
        </header>
        <!--==============================content================================-->
        <section id="content">
          <div class="container_12">
            <div class="wrapper p4">
              <article class="grid_10" style="margin-left:100px;">
                <div class="box" >
                  <div class="padding">
                  	<h3 class="p1">Rankings</h3>
                    <table class="rank" width="90%">
                    <tr><th><?php echo DEI_PLAYER; ?></th><th><?php echo DEI_MAPC; ?></th><th><?php echo DEI_SCORE; ?></th></tr>
                    <?php
                    $dao = new DataAccessObject();
					$sql = "SELECT u.nome AS utilizador, m.nome as mapa, j.pontuacao, j.data 
								from jogos j
								inner join utilizadores u on j.utilizador = u.id
								inner join mapas m on j.mapa = m.id
								order by pontuacao desc
								limit 0, 10";
					$params = array();
					$rows = $dao->ExecuteQuery($sql, $params);
					
					foreach($rows as $row){
						echo "<tr><td>" . $row['utilizador'] . "</td><td>" . $row['mapa'] . "</td><td>" . $row['pontuacao'] . "</td></tr>";
					}

					?>
                    </table>
                                     
                  </div>
                </div>
              </article>
            </div>
          </div>
          <div class="block"></div>
        </section>
      </div>
    </div>
    <!--==============================footer=================================-->
    <?php html_footer(); ?>
    <script type="text/javascript"> Cufon.now(); </script>
  </body>
</html>