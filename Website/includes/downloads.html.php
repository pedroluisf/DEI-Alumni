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
                  	<h3 class="p1">Downloads</h3>
					<div class="wrapper">
                        <figure class="img-indent"><img src="images/page1-img1.jpg" alt="" /></figure>
                        <div class="extra-wrap">
                            <h6 class="p1"><?php echo DEI_ABOUT1; ?></h6>
                            <?php echo DEI_ABOUT2; ?>
                            <div class="deialumni-1" style="margin-top:60px;"><a class="link" href="action.php?action=download"><?php echo DEI_DOWNLOAD; ?> <?php echo DEI_GAME; ?></a></div>
                            <a class="link-1" href="action.php?action=download"></a>
                        </div>
                    </div>   
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