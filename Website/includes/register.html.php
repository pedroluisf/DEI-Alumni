<?php ini_set('include_path', ini_get('include_path') . ':../includes'); ?>
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
          <? if(isset($_SESSION['dei::message'])) echo $_SESSION['dei::message']; ?>
					<div class="container_12">
						<div class="wrapper p4">
							<article class="grid_12">
								<div class="box">
                                	<h3 class="p1 padding"><strong><?php echo DEI_REGFORM; ?></strong></h3>
									<div style="text-align: justify; float: left; width: 300px; height: 300px;" class="padding"><?php echo DEI_REG_INFO; ?></div>
                                     <div class="padding" style="text-align: left; width:500px; float: right;">
									<form id="contact-form" action="action.php?action=register" method="post" enctype="multipart/form-data">
										<fieldset>
											<label><span class="text-form"><?php echo DEI_NAME; ?>:</span><input name="name" type="text" /></label>
                        				 	<label><span class="text-form"><?php echo DEI_USERNAME; ?>:</span><input name="username" type="text" /></label>
											<label><span class="text-form"><?php echo DEI_EMAIL; ?>:</span><input name="email" type="text" /></label>
                        					<label><span class="text-form"><?php echo DEI_PASSWORD; ?>:</span><input name="password" type="password" /></label>
											  <div class="wrapper">
												<div class="extra-wrap"  style="margin-right: 55px;">	
													<div class="clear"></div>
													<div class="buttons">
														<a class="button" href="#" onClick="document.getElementById('contact-form').submit()"><?php echo DEI_SUBMIT; ?></a>
													</div>
												</div>
											  </div>
										</fieldset>
									</form>
                                    
                                    </div>
                                    <div class="clear"></div>
                                    
                                    
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