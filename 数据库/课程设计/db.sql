-- MySQL dump 10.13  Distrib 5.7.26, for Linux (x86_64)
--
-- Host: localhost    Database: hospital
-- ------------------------------------------------------
-- Server version	5.7.26-0ubuntu0.18.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `MaT`
--

DROP TABLE IF EXISTS `MaT`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `MaT` (
  `Mno` char(20) NOT NULL,
  `Mname` char(20) NOT NULL,
  `Pri` float DEFAULT NULL,
  PRIMARY KEY (`Mno`),
  UNIQUE KEY `Mname` (`Mname`),
  UNIQUE KEY `Pri` (`Pri`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `MaT`
--

LOCK TABLES `MaT` WRITE;
/*!40000 ALTER TABLE `MaT` DISABLE KEYS */;
INSERT INTO `MaT` VALUES ('M1478541','aaaaa',10),('T148281','bbbbb',11.4);
/*!40000 ALTER TABLE `MaT` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Me_Re`
--

DROP TABLE IF EXISTS `Me_Re`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Me_Re` (
  `Sno` char(10) NOT NULL,
  `Pno` char(10) NOT NULL,
  `M_time` datetime DEFAULT NULL,
  `sym` char(200) DEFAULT NULL,
  `res` char(200) DEFAULT NULL,
  PRIMARY KEY (`Pno`),
  KEY `Sno` (`Sno`),
  CONSTRAINT `Me_Re_ibfk_1` FOREIGN KEY (`Sno`) REFERENCES `Stu` (`Sno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Me_Re`
--

LOCK TABLES `Me_Re` WRITE;
/*!40000 ALTER TABLE `Me_Re` DISABLE KEYS */;
INSERT INTO `Me_Re` VALUES ('0101170216','518303782','2019-06-02 01:14:43',NULL,NULL),('0101170216','613094889','2019-06-01 15:10:04','adsdczxzbkhsfz','asdBMCH Lgkhs,mdfn'),('0101170216','700752726','2019-06-02 02:23:05',NULL,NULL),('7541287964','758160045','2019-06-01 15:02:46',NULL,NULL),('0101170216','823546502','2019-06-01 23:30:21',NULL,NULL),('758426189','867173452','2019-06-01 15:06:35',NULL,NULL),('0101170216','918352714','2019-06-01 14:44:40',NULL,NULL);
/*!40000 ALTER TABLE `Me_Re` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Pre`
--

DROP TABLE IF EXISTS `Pre`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Pre` (
  `Pno` char(10) NOT NULL,
  `Mno` char(10) NOT NULL,
  `num` smallint(6) DEFAULT NULL,
  `mom_sum` float DEFAULT NULL,
  `payornot` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`Pno`,`Mno`),
  KEY `Mno` (`Mno`),
  CONSTRAINT `Pre_ibfk_1` FOREIGN KEY (`Mno`) REFERENCES `MaT` (`Mno`),
  CONSTRAINT `Pre_ibfk_2` FOREIGN KEY (`Pno`) REFERENCES `Me_Re` (`Pno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pre`
--

LOCK TABLES `Pre` WRITE;
/*!40000 ALTER TABLE `Pre` DISABLE KEYS */;
INSERT INTO `Pre` VALUES ('918352714','M1478541',4,114.24,0);
/*!40000 ALTER TABLE `Pre` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Stu`
--

DROP TABLE IF EXISTS `Stu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Stu` (
  `Sno` char(10) NOT NULL,
  `Sname` char(10) NOT NULL,
  `Age` smallint(6) NOT NULL,
  `indent` char(5) DEFAULT NULL,
  `MT` char(10) DEFAULT NULL,
  `mon_unpay` float DEFAULT NULL,
  `mon_payed` float DEFAULT NULL,
  `afr` float DEFAULT NULL,
  `collage` char(20) DEFAULT NULL,
  PRIMARY KEY (`Sno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Stu`
--

LOCK TABLES `Stu` WRITE;
/*!40000 ALTER TABLE `Stu` DISABLE KEYS */;
INSERT INTO `Stu` VALUES ('0101170216','蒋天济',19,'本科生','城镇居民',-456.96,456.96,0,'自动化院'),('0331171226','孙乾坤',19,'本科生','城镇居民',0,0,0,'自动化院'),('4857216485','刘顺达',19,'本科生','城镇职工',NULL,NULL,NULL,NULL),('587984645','asdija',22,'研究生','城镇居民',NULL,NULL,NULL,'计算机院'),('7541287964','陈文峰',19,'本科生','城镇居民',NULL,NULL,NULL,'自动化院'),('758426189','艾索德',21,'本科生','城镇职工',NULL,NULL,NULL,'地信院');
/*!40000 ALTER TABLE `Stu` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `Stu_fin`
--

DROP TABLE IF EXISTS `Stu_fin`;
/*!50001 DROP VIEW IF EXISTS `Stu_fin`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `Stu_fin` AS SELECT 
 1 AS `Sno`,
 1 AS `Sname`,
 1 AS `mon_unpay`,
 1 AS `mon_payed`,
 1 AS `afr`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `Stu_info`
--

DROP TABLE IF EXISTS `Stu_info`;
/*!50001 DROP VIEW IF EXISTS `Stu_info`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `Stu_info` AS SELECT 
 1 AS `Sno`,
 1 AS `Sname`,
 1 AS `Age`,
 1 AS `collage`,
 1 AS `indent`,
 1 AS `MT`*/;
SET character_set_client = @saved_cs_client;

--
-- Final view structure for view `Stu_fin`
--

/*!50001 DROP VIEW IF EXISTS `Stu_fin`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `Stu_fin` AS select `Stu`.`Sno` AS `Sno`,`Stu`.`Sname` AS `Sname`,`Stu`.`mon_unpay` AS `mon_unpay`,`Stu`.`mon_payed` AS `mon_payed`,`Stu`.`afr` AS `afr` from `Stu` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `Stu_info`
--

/*!50001 DROP VIEW IF EXISTS `Stu_info`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `Stu_info` AS select `Stu`.`Sno` AS `Sno`,`Stu`.`Sname` AS `Sname`,`Stu`.`Age` AS `Age`,`Stu`.`collage` AS `collage`,`Stu`.`indent` AS `indent`,`Stu`.`MT` AS `MT` from `Stu` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-03 14:15:59
