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
		<script src="js/tms-0.3.js" type="text/javascript"></script>
		<script src="js/tms_presets.js" type="text/javascript"></script>
		<script src="js/jquery.easing.1.3.js" type="text/javascript"></script>
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
	<body id="page1">
		<div class="extra">
			<div class="main">
<!--==============================header=================================-->
				<header>
          <?php require_once 'menu.inc.php'; ?>
					<div class="wrapper">
						<div class="slider-wrapper" style="margin-left: 162px;">
							<div class="slider">
								<ul class="items">
									<li><img src="images/slider-img1.jpg" alt="" /></li>
									<li><img src="images/slider-img2.jpg" alt="" /></li>
									<li><img src="images/slider-img3.jpg" alt="" /></li>
								</ul>
							</div>
							<a class="prev" href="#"></a>
							<a class="next" href="#"></a>
						</div>

					</div>
				</header>
<!--==============================content================================-->
				<section id="content">
					<div class="container_12">
						<div class="wrapper indent-bot">
							<article class="grid_4">
								<div class="box">
									<div class="padding">
										<div class="wrapper">
											<strong class="numb">01</strong>
											<div class="extra-wrap">
												<h2><?php echo DEI_MAP; ?></h2>
												<strong class="title-3"><?php echo DEI_BASIC; ?></strong>
											</div>
										</div>
										<div class="deialumni-1"><a class="link" href="work.php"><?php echo DEI_DOWNLOAD; ?> <?php echo DEI_MAP; ?></a></div>
									</div>
									<a class="link-1" href="#"></a>
								</div>
							</article>
							<article class="grid_4">
								<div class="box">
									<div class="padding">
										<div class="wrapper">
											<strong class="numb">02</strong>
											<div class="extra-wrap">
												<h2><?php echo DEI_MAP; ?></h2>
												<strong class="title-3"><?php echo DEI_MODERATE; ?></strong>
											</div>
										</div>
										<div class="deialumni-1"><a class="link" href="work.php"><?php echo DEI_DOWNLOAD; ?> <?php echo DEI_MAP; ?></a></div>
									</div>
									<a class="link-1" href="#"></a>
								</div>
							</article>
							<article class="grid_4">
								<div class="box">
									<div class="padding">
										<div class="wrapper">
											<strong class="numb">03</strong>
											<div class="extra-wrap">
												<h2><?php echo DEI_MAP; ?></h2>
												<strong class="title-3"><?php echo DEI_EXTREME; ?></strong>
											</div>
										</div>
										<div class="deialumni-1"><a class="link" href="work.php"><?php echo DEI_DOWNLOAD; ?> <?php echo DEI_MAP; ?></a></div>
									</div>
									<a class="link-1" href="#"></a>
								</div>
							</article>
						</div>
						<div class="wrapper">
							<article class="grid_8">
								<div class="indent-left indent-top img-indent-bot">
									<h3><?php echo DEI_ABOUTPRODS; ?></h3>
									<div class="wrapper">
										<figure class="img-indent"><img src="images/page1-img1.jpg" alt="" /></figure>
										<div class="extra-wrap">
											<h6 class="p1"><?php echo DEI_ABOUT1; ?></h6>
											<?php echo DEI_ABOUT2; ?>
										</div>
									</div>
								</div>
								<div class="wrapper">
									<article class="grid_4 alpha">
										<div class="indent-left">
											<ul class="list-1">
												<li><a href="work.php"><?php echo DEI_FEAT1; ?></a></li>
												<li><a href="work.php"><?php echo DEI_FEAT2; ?></a></li>
												<li><a href="work.php"><?php echo DEI_FEAT3; ?></a></li>
											</ul>
										</div>
									</article>
									<article class="grid_4 omega">
										<div class="indent-left">
											<ul class="list-1">
												<li><a href="work.php"><?php echo DEI_FEAT4; ?></a></li>
												<li><a href="work.php"><?php echo DEI_FEAT5; ?></a></li>
												<li><a href="work.php"><?php echo DEI_FEAT6; ?></a></li>
											</ul>
										</div>
									</article>
								</div>
							</article>
							<article class="grid_4">
								<div class="box-2">
									<div class="padding">
										<h3><?php echo DEI_REVIEWS; ?></h3>
										<div class="border-bot prev-indent-bot">
											<blockquote>
												<div class="padding-left">
													<p class="p1">iLike it!</p>
													<strong>Steve Jobs</strong>
												</div>
											</blockquote>
										</div>
										<div class="border-bot p2">
											<blockquote>
												<div class="padding-left">
													<p class="p1">Crazy little thing...</p>
													<strong>Elvis Presley</strong>
												</div>
											</blockquote>
										</div>
										<div class="indent-left">
											<a class="link-2" href="work.php"><?php echo DEI_READMORE; ?></a>
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
		<script type="text/javascript">
			$(window).load(function() {
				$('.slider')._TMS({
					duration:800,
					easing:'easeOutQuad',
					preset:'simpleFade',
					slideshow:7000,
					banners:false,
					pauseOnHover:true,
					pagination:false,
					nextBu:'.next',
					prevBu:'.prev'
				});
			});
		</script>
	</body>
</html>