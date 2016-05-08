//////////////////////////////////////////////////////////////////////////////
//
//	BHMorse.cpp - Library for Morse code
//
//	Copyright © 2016 Robert L. Bailey
//
//	Send Morse Code, including generating random characters, groups of
//	characters, or plausible QSOs.
//
//////////////////////////////////////////////////////////////////////////////
//
//	This file is part of BHMorse.
//
//	BHMorse is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	BHMorse is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with BHMorse.  If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <EEPROM.h>
#include "BHMorse.h"

//////////////////////////////////////////////////////////////////////////////
// Stuff available for random senders
//////////////////////////////////////////////////////////////////////////////

// names

const BHMorse::firstName_t BHMorse::_firstNames[] PROGMEM =
{
	{ "AALIYAH" },
	{ "AARAV" },
	{ "AARON" },
	{ "ABBOTT" },
	{ "ABBY" },
	{ "ABEL" },
	{ "ABIGAIL" },
	{ "ABNER" },
	{ "ABRAHAM" },
	{ "ADAM" },
	{ "ADDISON" },
	{ "ADI" },
	{ "ADLER" },
	{ "ADLEY" },
	{ "ADRIAN" },
	{ "AGUSTIN" },
	{ "AI" },
	{ "AIDEN" },
	{ "AIKEN" },
	{ "ALAN" },
	{ "ALANA" },
	{ "ALBERN" },
	{ "ALBERT" },
	{ "ALBION" },
	{ "ALDEN" },
	{ "ALDIS" },
	{ "ALDRICH" },
	{ "ALEX" },
	{ "ALEXA" },
	{ "ALEXANDER" },
	{ "ALEXIA" },
	{ "ALEXIS" },
	{ "ALFIE" },
	{ "ALFRED" },
	{ "ALICIA" },
	{ "ALIYAH" },
	{ "ALLAN" },
	{ "ALLISON" },
	{ "ALONDRA" },
	{ "ALSTON" },
	{ "ALTON" },
	{ "ALVIN" },
	{ "ALYSSA" },
	{ "AMANDA" },
	{ "AMAYA" },
	{ "AMBER" },
	{ "AMBROSE" },
	{ "AMELIA" },
	{ "AMERY" },
	{ "AMIT" },
	{ "AMOS" },
	{ "AMY" },
	{ "ANA" },
	{ "ANDREA" },
	{ "ANDREAS" },
	{ "ANDREI" },
	{ "ANDREW" },
	{ "ANDY" },
	{ "ANGEL" },
	{ "ANGELA" },
	{ "ANGELICA" },
	{ "ANGELINA" },
	{ "ANGUS" },
	{ "ANIYAH" },
	{ "ANNA" },
	{ "ANSEL" },
	{ "ANSON" },
	{ "ANTHONY" },
	{ "ANTONIO" },
	{ "ARATA" },
	{ "ARCHER" },
	{ "ARIANA" },
	{ "ARIANNA" },
	{ "ARIEL" },
	{ "ARLEN" },
	{ "ARNOLD" },
	{ "ARON" },
	{ "ART" },
	{ "ARTHUR" },
	{ "ARVEL" },
	{ "ASAHI" },
	{ "ASHER" },
	{ "ASHLEY" },
	{ "ASHLYN" },
	{ "ATTICUS" },
	{ "ATWATER" },
	{ "ATWOOD" },
	{ "AUBREY" },
	{ "AUDREY" },
	{ "AUSTIN" },
	{ "AUTUMN" },
	{ "AVA" },
	{ "AVERY" },
	{ "AXEL" },
	{ "AYA" },
	{ "AZIZ" },
	{ "BAILEY" },
	{ "BAIRD" },
	{ "BALDWIN" },
	{ "BARB" },
	{ "BARBARA" },
	{ "BARBIE" },
	{ "BARCLAY" },
	{ "BARNABY" },
	{ "BARON" },
	{ "BARRETT" },
	{ "BARRY" },
	{ "BART" },
	{ "BASIL" },
	{ "BELLA" },
	{ "BEN" },
	{ "BENEDICT" },
	{ "BENTON" },
	{ "BERNARD" },
	{ "BERT" },
	{ "BETHANY" },
	{ "BETTY" },
	{ "BEVIS" },
	{ "BIANCA" },
	{ "BILL" },
	{ "BLAINE" },
	{ "BLAIR" },
	{ "BLAKE" },
	{ "BOB" },
	{ "BOBBIE" },
	{ "BOND" },
	{ "BORIS" },
	{ "BOWEN" },
	{ "BRADEN" },
	{ "BRADLEY" },
	{ "BRANDAN" },
	{ "BRANDON" },
	{ "BREANNA" },
	{ "BRENDA" },
	{ "BRENDAN" },
	{ "BRENDON" },
	{ "BRENT" },
	{ "BRETT" },
	{ "BRIAN" },
	{ "BRIANA" },
	{ "BRIANNA" },
	{ "BRICE" },
	{ "BRIGHAM" },
	{ "BROCK" },
	{ "BROOKE" },
	{ "BRUCE" },
	{ "BRUNO" },
	{ "BRYANT" },
	{ "BUCK" },
	{ "BUD" },
	{ "BURGESS" },
	{ "BURTON" },
	{ "BYRON" },
	{ "CADENCE" },
	{ "CADMAN" },
	{ "CAITLIN" },
	{ "CAITLYN" },
	{ "CALDWELL" },
	{ "CALEB" },
	{ "CALVERT" },
	{ "CALVIN" },
	{ "CAMILA" },
	{ "CAMRYN" },
	{ "CARL" },
	{ "CARLTON" },
	{ "CARLY" },
	{ "CARNEY" },
	{ "CAROL" },
	{ "CAROLINE" },
	{ "CAROLYN" },
	{ "CARRICK" },
	{ "CARROLL" },
	{ "CARTER" },
	{ "CARVER" },
	{ "CARY" },
	{ "CASEY" },
	{ "CASPER" },
	{ "CASSIDY" },
	{ "CATHY" },
	{ "CECIL" },
	{ "CEDRIC" },
	{ "CHAD" },
	{ "CHANDLER" },
	{ "CHANNING" },
	{ "CHAPMAN" },
	{ "CHARLES" },
	{ "CHARLIE" },
	{ "CHATWIN" },
	{ "CHELSEA" },
	{ "CHESTER" },
	{ "CHEYENNE" },
	{ "CHLOE" },
	{ "CHRIS" },
	{ "CHRISTIAN" },
	{ "CHRISTINE" },
	{ "CIARA" },
	{ "CLAIRE" },
	{ "CLARA" },
	{ "CLARENCE" },
	{ "CLAUDE" },
	{ "CLAY" },
	{ "CLAYTON" },
	{ "CLIFF" },
	{ "CLIVE" },
	{ "CLYDE" },
	{ "COLEMAN" },
	{ "COLIN" },
	{ "COLLIER" },
	{ "CONAN" },
	{ "CONNELL" },
	{ "CONNOR" },
	{ "CONRAD" },
	{ "CONROY" },
	{ "CONWAY" },
	{ "CORWIN" },
	{ "COURTNEY" },
	{ "CRAIG" },
	{ "CRISPIN" },
	{ "CROSBY" },
	{ "CRYSTAL" },
	{ "CULBERT" },
	{ "CULVER" },
	{ "CURT" },
	{ "CURTIS" },
	{ "CYNTHIA" },
	{ "CYRIL" },
	{ "DAISY" },
	{ "DAKOTA" },
	{ "DALE" },
	{ "DALTON" },
	{ "DAMON" },
	{ "DANIEL" },
	{ "DANIELA" },
	{ "DANIELLE" },
	{ "DARCY" },
	{ "DARELL" },
	{ "DARIAN" },
	{ "DAVE" },
	{ "DAVID" },
	{ "DAVIN" },
	{ "DAVIT" },
	{ "DEAN" },
	{ "DEBORAH" },
	{ "DEBRA" },
	{ "DECLAN" },
	{ "DELANEY" },
	{ "DELMAR" },
	{ "DENLEY" },
	{ "DENNIS" },
	{ "DEREK" },
	{ "DERMOT" },
	{ "DERWIN" },
	{ "DESMOND" },
	{ "DESTINY" },
	{ "DEXTER" },
	{ "DIANA" },
	{ "DIANE" },
	{ "DICK" },
	{ "DIEGO" },
	{ "DILLON" },
	{ "DION" },
	{ "DIRK" },
	{ "DIXON" },
	{ "DOMINIC" },
	{ "DONALD" },
	{ "DONNA" },
	{ "DORIAN" },
	{ "DOROTHY" },
	{ "DOUGLAS" },
	{ "DOYLE" },
	{ "DRAKE" },
	{ "DREW" },
	{ "DRISCOLL" },
	{ "DUDLEY" },
	{ "DUNCAN" },
	{ "DURWIN" },
	{ "DWAYNE" },
	{ "DWIGHT" },
	{ "DYLAN" },
	{ "EARL" },
	{ "EATON" },
	{ "EBENEZER" },
	{ "ED" },
	{ "EDAN" },
	{ "EDDIE" },
	{ "EDGAR" },
	{ "EDMOND" },
	{ "EDRIC" },
	{ "EDWARD" },
	{ "EDWIN" },
	{ "EFRAIN" },
	{ "EGAN" },
	{ "EGBERT" },
	{ "EGERTON" },
	{ "EGIL" },
	{ "ELBERT" },
	{ "ELDON" },
	{ "ELDWIN" },
	{ "ELEANOR" },
	{ "ELENA" },
	{ "ELI" },
	{ "ELIAS" },
	{ "ELIJAH" },
	{ "ELISE" },
	{ "ELIZABETH" },
	{ "ELLA" },
	{ "ELLERY" },
	{ "ELLIE" },
	{ "ELLIOTT" },
	{ "ELMER" },
	{ "ELROY" },
	{ "ELTON" },
	{ "ELVIS" },
	{ "ELY" },
	{ "EMERY" },
	{ "EMILY" },
	{ "EMMA" },
	{ "EMMANUEL" },
	{ "EMMETT" },
	{ "EMRICK" },
	{ "ENOCH" },
	{ "ERIC" },
	{ "ERICA" },
	{ "ERIK" },
	{ "ERIKA" },
	{ "ERIN" },
	{ "ERNEST" },
	{ "ERROL" },
	{ "ERSKINE" },
	{ "ERWIN" },
	{ "ESMOND" },
	{ "ETHAN" },
	{ "ETHEN" },
	{ "EUGENE" },
	{ "EVA" },
	{ "EVAN" },
	{ "EVELYN" },
	{ "EVERETT" },
	{ "EZRA" },
	{ "FABIAN" },
	{ "FAIRFAX" },
	{ "FAITH" },
	{ "FALKNER" },
	{ "FARLEY" },
	{ "FARRELL" },
	{ "FATIMA" },
	{ "FELIX" },
	{ "FENG" },
	{ "FENTON" },
	{ "FERDINAND" },
	{ "FERGAL" },
	{ "FERGUSON" },
	{ "FERRIS" },
	{ "FILIP" },
	{ "FINBAR" },
	{ "FLEMING" },
	{ "FLETCHER" },
	{ "FLOYD" },
	{ "FORBES" },
	{ "FORREST" },
	{ "FOSTER" },
	{ "FOX" },
	{ "FRANCIS" },
	{ "FRANCISCO" },
	{ "FRANK" },
	{ "FRASIER" },
	{ "FREEMAN" },
	{ "FREJA" },
	{ "GABRIEL" },
	{ "GABRIELA" },
	{ "GABRIELLE" },
	{ "GALE" },
	{ "GALVIN" },
	{ "GARDNER" },
	{ "GARRET" },
	{ "GARRICK" },
	{ "GARTH" },
	{ "GARY" },
	{ "GAVIN" },
	{ "GENESIS" },
	{ "GEORGE" },
	{ "GEORGI" },
	{ "GERALD" },
	{ "GIANNA" },
	{ "GIDEON" },
	{ "GIFFORD" },
	{ "GILBERT" },
	{ "GILES" },
	{ "GILROY" },
	{ "GISELLE" },
	{ "GLENN" },
	{ "GODDARD" },
	{ "GODFREY" },
	{ "GODWIN" },
	{ "GOR" },
	{ "GRACE" },
	{ "GRACIE" },
	{ "GRAHAM" },
	{ "GRANT" },
	{ "GRAYSON" },
	{ "GREG" },
	{ "GREGORY" },
	{ "GRESHAM" },
	{ "GRISWALD" },
	{ "GROVER" },
	{ "GUY" },
	{ "HADDEN" },
	{ "HADLEY" },
	{ "HADWIN" },
	{ "HAILEY" },
	{ "HAL" },
	{ "HALBERT" },
	{ "HALDEN" },
	{ "HALE" },
	{ "HALEY" },
	{ "HALL" },
	{ "HALSEY" },
	{ "HAMLIN" },
	{ "HANK" },
	{ "HANLEY" },
	{ "HANNA" },
	{ "HANNAH" },
	{ "HANS" },
	{ "HAO" },
	{ "HARDY" },
	{ "HARLAN" },
	{ "HARLEY" },
	{ "HAROLD" },
	{ "HARRIS" },
	{ "HARRY" },
	{ "HARTLEY" },
	{ "HARUKI" },
	{ "HARUTA" },
	{ "HAYLEE" },
	{ "HEATH" },
	{ "HEATHER" },
	{ "HEAVEN" },
	{ "HECTOR" },
	{ "HELEN" },
	{ "HENRY" },
	{ "HERBERT" },
	{ "HERMAN" },
	{ "HINATA" },
	{ "HIROTO" },
	{ "HOMER" },
	{ "HOPE" },
	{ "HORACE" },
	{ "HORATIO" },
	{ "HOWARD" },
	{ "HUBERT" },
	{ "HUGH" },
	{ "HUGO" },
	{ "HUMPHREY" },
	{ "HUNTER" },
	{ "IAN" },
	{ "ICHIKA" },
	{ "IGOR" },
	{ "IOANNIS" },
	{ "IRVIN" },
	{ "IRVING" },
	{ "ISAAC" },
	{ "ISABEL" },
	{ "ISABELLA" },
	{ "ISABELLE" },
	{ "ISAIAH" },
	{ "ITSUKI" },
	{ "IVAN" },
	{ "IVER" },
	{ "IVES" },
	{ "JACK" },
	{ "JACKSON" },
	{ "JACOB" },
	{ "JADA" },
	{ "JADE" },
	{ "JADYN" },
	{ "JAKOB" },
	{ "JAMES" },
	{ "JAMIE" },
	{ "JAN" },
	{ "JANE" },
	{ "JANET" },
	{ "JARVIS" },
	{ "JASMIN" },
	{ "JASMINE" },
	{ "JASON" },
	{ "JASPER" },
	{ "JAVIER" },
	{ "JAYDEN" },
	{ "JAYLA" },
	{ "JAZMIN" },
	{ "JAZMINE" },
	{ "JED" },
	{ "JEFF" },
	{ "JEFFREY" },
	{ "JENNA" },
	{ "JENNIFER" },
	{ "JEREMIAH" },
	{ "JEREMY" },
	{ "JEROME" },
	{ "JERRY" },
	{ "JESSE" },
	{ "JESSICA" },
	{ "JIAN" },
	{ "JIE" },
	{ "JILLIAN" },
	{ "JIM" },
	{ "JIMMY" },
	{ "JOAO" },
	{ "JOCELYN" },
	{ "JOE" },
	{ "JOEY" },
	{ "JOHN" },
	{ "JONAS" },
	{ "JONATHAN" },
	{ "JORDAN" },
	{ "JORDYN" },
	{ "JOSE" },
	{ "JOSEPH" },
	{ "JOSEPHINE" },
	{ "JOSHUA" },
	{ "JUAN" },
	{ "JULIA" },
	{ "JULIANA" },
	{ "JULIANNA" },
	{ "JUN" },
	{ "JUSTIN" },
	{ "KAITLYN" },
	{ "KANE" },
	{ "KAREN" },
	{ "KARINA" },
	{ "KARLA" },
	{ "KATE" },
	{ "KATELYN" },
	{ "KATHRYN" },
	{ "KATIE" },
	{ "KATRINA" },
	{ "KAYLA" },
	{ "KAYLEE" },
	{ "KEATON" },
	{ "KEEGAN" },
	{ "KEENE" },
	{ "KEIRA" },
	{ "KEITH" },
	{ "KELLY" },
	{ "KELSEY" },
	{ "KELVIN" },
	{ "KEN" },
	{ "KENDALL" },
	{ "KENDRICK" },
	{ "KENNEDY" },
	{ "KENNETH" },
	{ "KENT" },
	{ "KENWAY" },
	{ "KENYON" },
	{ "KERRY" },
	{ "KERWIN" },
	{ "KEVIN" },
	{ "KIARA" },
	{ "KIEFER" },
	{ "KILBY" },
	{ "KILIAN" },
	{ "KIM" },
	{ "KIMBALL" },
	{ "KIMBERLY" },
	{ "KINGSLEY" },
	{ "KIRA" },
	{ "KIRBY" },
	{ "KIRK" },
	{ "KIT" },
	{ "KODY" },
	{ "KONRAD" },
	{ "KURT" },
	{ "KYLA" },
	{ "KYLE" },
	{ "KYLEE" },
	{ "KYLIE" },
	{ "KYRA" },
	{ "LAILA" },
	{ "LAMBERT" },
	{ "LAMONT" },
	{ "LANCELOT" },
	{ "LANDON" },
	{ "LANDRY" },
	{ "LANE" },
	{ "LARA" },
	{ "LARRY" },
	{ "LARS" },
	{ "LAURA" },
	{ "LAUREN" },
	{ "LAURENCE" },
	{ "LAYLA" },
	{ "LEAH" },
	{ "LEE" },
	{ "LEITH" },
	{ "LEO" },
	{ "LEON" },
	{ "LEONARD" },
	{ "LEROY" },
	{ "LESLIE" },
	{ "LESTER" },
	{ "LEWIS" },
	{ "LEXI" },
	{ "LIAM" },
	{ "LILIANA" },
	{ "LILLIAN" },
	{ "LILLY" },
	{ "LILY" },
	{ "LINCOLN" },
	{ "LINDA" },
	{ "LINDSAY" },
	{ "LINDSEY" },
	{ "LIONEL" },
	{ "LISA" },
	{ "LIZ" },
	{ "LLOYD" },
	{ "LOGAN" },
	{ "LOMBARD" },
	{ "LOUIS" },
	{ "LOWELL" },
	{ "LUCAS" },
	{ "LUCIA" },
	{ "LUCY" },
	{ "LUIS" },
	{ "LUKAS" },
	{ "LUKE" },
	{ "LUTHER" },
	{ "LYDIA" },
	{ "LYNDON" },
	{ "MACKENZIE" },
	{ "MACY" },
	{ "MADDOX" },
	{ "MADELINE" },
	{ "MADELYN" },
	{ "MADISON" },
	{ "MAGGIE" },
	{ "MAGNUS" },
	{ "MAIA" },
	{ "MAKAYLA" },
	{ "MAKENNA" },
	{ "MAKENZIE" },
	{ "MALCOLM" },
	{ "MALIK" },
	{ "MALLORY" },
	{ "MARC" },
	{ "MARCUS" },
	{ "MARGARET" },
	{ "MARIA" },
	{ "MARIAH" },
	{ "MARIANA" },
	{ "MARISSA" },
	{ "MARK" },
	{ "MARLON" },
	{ "MARTIN" },
	{ "MARVIN" },
	{ "MARY" },
	{ "MASON" },
	{ "MATEO" },
	{ "MATHIS" },
	{ "MATIAS" },
	{ "MATT" },
	{ "MATTHEW" },
	{ "MAURICE" },
	{ "MAX" },
	{ "MAXIM" },
	{ "MAYA" },
	{ "MCKENNA" },
	{ "MCKENZIE" },
	{ "MEDWIN" },
	{ "MEGAN" },
	{ "MEHMET" },
	{ "MELANIE" },
	{ "MELISSA" },
	{ "MELVILLE" },
	{ "MELVIN" },
	{ "MERLIN" },
	{ "MIA" },
	{ "MICHAEL" },
	{ "MICHELLE" },
	{ "MIGUEL" },
	{ "MIKAYLA" },
	{ "MIKE" },
	{ "MILBURN" },
	{ "MILES" },
	{ "MILO" },
	{ "MIN JOON" },
	{ "MINATO" },
	{ "MIRANDA" },
	{ "MISSY" },
	{ "MOLLY" },
	{ "MONICA" },
	{ "MONROE" },
	{ "MONTAGUE" },
	{ "MORGAN" },
	{ "MORRIS" },
	{ "MORTON" },
	{ "MOSHE" },
	{ "MURRAY" },
	{ "MYA" },
	{ "NADIA" },
	{ "NANCY" },
	{ "NAOMI" },
	{ "NAREK" },
	{ "NATALIA" },
	{ "NATALIE" },
	{ "NATHAN" },
	{ "NEAL" },
	{ "NEVAEH" },
	{ "NEVILLE" },
	{ "NICHOLAS" },
	{ "NICK" },
	{ "NICOLAS" },
	{ "NICOLE" },
	{ "NIGEL" },
	{ "NOA" },
	{ "NOAH" },
	{ "NOAM" },
	{ "NOEL" },
	{ "NORMAN" },
	{ "NORRIS" },
	{ "OLAF" },
	{ "OLIN" },
	{ "OLIVER" },
	{ "OLIVIA" },
	{ "OMAR" },
	{ "ONNI" },
	{ "ORSON" },
	{ "OSCAR" },
	{ "OSWALD" },
	{ "OTIS" },
	{ "OWEN" },
	{ "PABLO" },
	{ "PAIGE" },
	{ "PAMELA" },
	{ "PARIS" },
	{ "PAT" },
	{ "PATRICK" },
	{ "PATTIE" },
	{ "PATTY" },
	{ "PAUL" },
	{ "PAXTON" },
	{ "PAYTON" },
	{ "PEDRO" },
	{ "PENELOPE" },
	{ "PERCY" },
	{ "PERRY" },
	{ "PETER" },
	{ "PEYTON" },
	{ "PHILBERT" },
	{ "PHILIP" },
	{ "PHINEAS" },
	{ "PIERCE" },
	{ "QIAN" },
	{ "QUADE" },
	{ "QUENBY" },
	{ "QUENTIN" },
	{ "QUILLAN" },
	{ "QUIMBY" },
	{ "QUINBY" },
	{ "QUINCY" },
	{ "QUINLAN" },
	{ "QUINN" },
	{ "RACHEL" },
	{ "RALPH" },
	{ "RAMSEY" },
	{ "RANDOLPH" },
	{ "RAYMOND" },
	{ "REAGAN" },
	{ "REBECCA" },
	{ "REESE" },
	{ "REGINALD" },
	{ "REN" },
	{ "RENFRED" },
	{ "RENZ" },
	{ "REX" },
	{ "RHETT" },
	{ "RICH" },
	{ "RICHARD" },
	{ "RICHIE" },
	{ "RICK" },
	{ "RIDLEY" },
	{ "RIKO" },
	{ "RILEY" },
	{ "ROB" },
	{ "ROBERT" },
	{ "ROBIN" },
	{ "ROD" },
	{ "RODERICK" },
	{ "RODNEY" },
	{ "RODRIGO" },
	{ "ROGER" },
	{ "ROLAND" },
	{ "ROLF" },
	{ "RON" },
	{ "RONALD" },
	{ "RORY" },
	{ "ROSS" },
	{ "ROSWELL" },
	{ "ROY" },
	{ "ROYCE" },
	{ "RUBY" },
	{ "RUFUS" },
	{ "RUPERT" },
	{ "RUSSELL" },
	{ "RUTH" },
	{ "RYAN" },
	{ "RYLEE" },
	{ "SABRINA" },
	{ "SADIE" },
	{ "SAKURA" },
	{ "SAM" },
	{ "SAMANTHA" },
	{ "SAMSON" },
	{ "SAMUEL" },
	{ "SANDY" },
	{ "SANTIAGO" },
	{ "SARA" },
	{ "SARAH" },
	{ "SAVANNAH" },
	{ "SCOTT" },
	{ "SEAN" },
	{ "SEBASTIAN" },
	{ "SELENA" },
	{ "SERENITY" },
	{ "SETH" },
	{ "SEYMOUR" },
	{ "SHAMUS" },
	{ "SHANE" },
	{ "SHARON" },
	{ "SHAWN" },
	{ "SHELBY" },
	{ "SHELLEY" },
	{ "SHERARD" },
	{ "SHERIDAN" },
	{ "SHERLOCK" },
	{ "SHERMAN" },
	{ "SHERWIN" },
	{ "SHIRA" },
	{ "SHIRLEY" },
	{ "SHU" },
	{ "SIDNEY" },
	{ "SIERRA" },
	{ "SIGMUND" },
	{ "SILAS" },
	{ "SIMON" },
	{ "SINCLAIR" },
	{ "SKYLAR" },
	{ "SLOANE" },
	{ "SOFIA" },
	{ "SOLOMON" },
	{ "SOMCHAI" },
	{ "SOMSAK" },
	{ "SOPHIA" },
	{ "SOPHIE" },
	{ "SOU" },
	{ "SOUTA" },
	{ "SPENCER" },
	{ "STACY" },
	{ "STAN" },
	{ "STANLEY" },
	{ "STEFAN" },
	{ "STELLA" },
	{ "STEPH" },
	{ "STEPHANIE" },
	{ "STEPHEN" },
	{ "STERLING" },
	{ "STEVE" },
	{ "STEWART" },
	{ "STUART" },
	{ "SUE" },
	{ "SUMMER" },
	{ "SYDNEY" },
	{ "TALIA" },
	{ "TAMAR" },
	{ "TATSUKI" },
	{ "TAYLOR" },
	{ "THEOBOLD" },
	{ "THEODORE" },
	{ "THOMAS" },
	{ "TIBERIUS" },
	{ "TIFFANY" },
	{ "TIM" },
	{ "TIMOTHY" },
	{ "TITUS" },
	{ "TOBIAS" },
	{ "TOBY" },
	{ "TODD" },
	{ "TOM" },
	{ "TOMAS" },
	{ "TOMMY" },
	{ "TOMOHARU" },
	{ "TONY" },
	{ "TRAVIS" },
	{ "TRENT" },
	{ "TREVOR" },
	{ "TRINITY" },
	{ "TRISTAN" },
	{ "TROY" },
	{ "TRUMAN" },
	{ "TSURUKI" },
	{ "TYLER" },
	{ "UDOLF" },
	{ "UNWIN" },
	{ "URIAH" },
	{ "VALERIA" },
	{ "VALERIE" },
	{ "VANCE" },
	{ "VANESSA" },
	{ "VAUGHAN" },
	{ "VERNON" },
	{ "VERONICA" },
	{ "VICTOR" },
	{ "VICTORIA" },
	{ "VINCENT" },
	{ "VIRGINIA" },
	{ "VIVIAN" },
	{ "WALLACE" },
	{ "WALTER" },
	{ "WALTON" },
	{ "WARD" },
	{ "WARREN" },
	{ "WAYNE" },
	{ "WEI" },
	{ "WESLEY" },
	{ "WILBUR" },
	{ "WILL" },
	{ "WILLARD" },
	{ "WILLIAM" },
	{ "WILLIS" },
	{ "WINSTON" },
	{ "WINTHROP" },
	{ "WOUT" },
	{ "WYATT" },
	{ "WYLIE" },
	{ "WYMAN" },
	{ "XIAN" },
	{ "YAEL" },
	{ "YI" },
	{ "YONG" },
	{ "YUSUF" },
	{ "YUUMA" },
	{ "YUVAL" },
	{ "ZACHARIAH" },
	{ "ZACHARY" },
	{ "ZANE" },
	{ "ZEBADIAH" },
	{ "ZEBEDIAH" },
	{ "ZOE" },
	{ "ZOEY" }
};

// cities

const BHMorse::city_t BHMorse::_cities[] PROGMEM =
{
	{ "ABILENE TX" },
	{ "AHMEDABAD" },
	{ "AKRON OH" },
	{ "ALBUQUERQUE NM" },
	{ "ALEXANDRIA VA" },
	{ "ALLENTOWN PA" },
	{ "AMARILLO TX" },
	{ "ANAHEIM CA" },
	{ "ANCHORAGE AK" },
	{ "ANKARA" },
	{ "ANN ARBOR MI" },
	{ "ANTIOCH CA" },
	{ "ARLINGTON TX" },
	{ "ARVADA CO" },
	{ "ATHENS GA" },
	{ "ATLANTA GA" },
	{ "AUGUSTA GA" },
	{ "AURORA CO" },
	{ "AURORA IL" },
	{ "AUSTIN TX" },
	{ "AVONDALE PA" },
	{ "BAKERSFIELD CA" },
	{ "BALTIMORE MD" },
	{ "BANGALORE" },
	{ "BANGKOK" },
	{ "BARCELONA" },
	{ "BATON ROUGE LA" },
	{ "BEAUMONT TX" },
	{ "BEIJING" },
	{ "BELLEVUE WA" },
	{ "BELO HORIZONTE" },
	{ "BERKELEY CA" },
	{ "BERLIN" },
	{ "BILLINGS MT" },
	{ "BIRMINGHAM AL" },
	{ "BOGOTA" },
	{ "BOISE ID" },
	{ "BOSTON MA" },
	{ "BOULDER CO" },
	{ "BRIDGEPORT CT" },
	{ "BROKEN ARROW OK" },
	{ "BROWNSVILLE TX" },
	{ "BUFFALO NY" },
	{ "BURBANK CA" },
	{ "CAMBRIDGE MA" },
	{ "CAPE CORAL FL" },
	{ "CARLSBAD CA" },
	{ "CARROLLTON TX" },
	{ "CARY NC" },
	{ "CEDAR RAPIDS IA" },
	{ "CENTENNIAL CO" },
	{ "CHANDLER AZ" },
	{ "CHARLESTON SC" },
	{ "CHARLESTON WV" },
	{ "CHARLOTTE NC" },
	{ "CHATTANOOGA TN" },
	{ "CHENGDU" },
	{ "CHENNAI" },
	{ "CHESAPEAKE VA" },
	{ "CHEYENNE WY" },
	{ "CHICAGO IL" },
	{ "CHONGQING" },
	{ "CHULA VISTA CA" },
	{ "CINCINNATI OH" },
	{ "CLARKSVILLE TN" },
	{ "CLEARWATER FL" },
	{ "CLEVELAND OH" },
	{ "CLOVIS CA" },
	{ "COLLEGE STATION TX" },
	{ "COLORADO SPRINGS CO" },
	{ "COLUMBIA MO" },
	{ "COLUMBIA SC" },
	{ "COLUMBUS GA" },
	{ "COLUMBUS OH" },
	{ "CONCORD CA" },
	{ "CORAL SPRINGS FL" },
	{ "CORONA CA" },
	{ "CORPUS CHRISTI TX" },
	{ "COSTA MESA CA" },
	{ "DALLAS TX" },
	{ "DALY CITY CA" },
	{ "DAVENPORT IA" },
	{ "DAYTON OH" },
	{ "DENTON TX" },
	{ "DENVER CO" },
	{ "DES MOINES IA" },
	{ "DETROIT MI" },
	{ "DHAKA" },
	{ "DOWNEY CA" },
	{ "DURHAM NC" },
	{ "EDISON NJ" },
	{ "EL CAJON CA" },
	{ "EL MONTE CA" },
	{ "EL PASO TX" },
	{ "ELGIN IL" },
	{ "ELIZABETH NJ" },
	{ "ELK GROVE CA" },
	{ "ESCONDIDO CA" },
	{ "EUGENE OR" },
	{ "EVANSVILLE IN" },
	{ "EVERETT WA" },
	{ "FAIRFIELD CA" },
	{ "FARGO ND" },
	{ "FAYETTEVILLE NC" },
	{ "FONTANA CA" },
	{ "FORT COLLINS CO" },
	{ "FORT LAUDERDALE FL" },
	{ "FORT WAYNE IN" },
	{ "FORT WORTH TX" },
	{ "FRANKFURT" },
	{ "FREMONT CA" },
	{ "FRESNO CA" },
	{ "FRIENDSWOOD TX" },
	{ "FRISCO TX" },
	{ "FULLERTON CA" },
	{ "GAINESVILLE FL" },
	{ "GARDEN GROVE CA" },
	{ "GARLAND TX" },
	{ "GILBERT AZ" },
	{ "GLENDALE AZ" },
	{ "GLENDALE CA" },
	{ "GRAND PRAIRIE TX" },
	{ "GRAND RAPIDS MI" },
	{ "GREEN BAY WI" },
	{ "GREENSBORO NC" },
	{ "GRESHAM OR" },
	{ "GUADALAJARA" },
	{ "GUANGZHOU" },
	{ "HAMBURG" },
	{ "HAMPTON VA" },
	{ "HANGZHOU" },
	{ "HARTFORD CT" },
	{ "HAYWARD CA" },
	{ "HENDERSON NV" },
	{ "HIALEAH FL" },
	{ "HIGH POINT NC" },
	{ "HOLLYWOOD FL" },
	{ "HONG KONG" },
	{ "HONOLULU HI" },
	{ "HOUSTON TX" },
	{ "HUNTINGTON BEACH CA" },
	{ "HUNTSVILLE AL" },
	{ "HURRICANE WV" },
	{ "HYDERABAD" },
	{ "INDEPENDENCE MO" },
	{ "INDIANAPOLIS IN" },
	{ "INGLEWOOD CA" },
	{ "IRVINE CA" },
	{ "IRVING TX" },
	{ "ISTANBUL" },
	{ "JACKSON MS" },
	{ "JACKSONVILLE FL" },
	{ "JAKARTA" },
	{ "JERSEY CITY NJ" },
	{ "JOLIET IL" },
	{ "KANSAS  MO" },
	{ "KANSAS CITY KS" },
	{ "KANSAS CITY MO" },
	{ "KARACHI" },
	{ "KENNETT SQUARE PA" },
	{ "KENT WA" },
	{ "KILLEEN TX" },
	{ "KNOXVILLE TN" },
	{ "KOLKATA" },
	{ "LAFAYETTE LA" },
	{ "LAGOS" },
	{ "LAKELAND FL" },
	{ "LAKEWOOD CO" },
	{ "LANCASTER CA" },
	{ "LANSING MI" },
	{ "LAREDO TX" },
	{ "LAS CRUCES NM" },
	{ "LAS VEGAS NV" },
	{ "LEWISVILLE TX" },
	{ "LEXINGTON KY" },
	{ "LIMA" },
	{ "LINCOLN NE" },
	{ "LITTLE ROCK AR" },
	{ "LONDON UK" },
	{ "LONG BEACH CA" },
	{ "LOS ANGELES CA" },
	{ "LOUISVILLE KY" },
	{ "LOWELL MA" },
	{ "LUANDA" },
	{ "LUBBOCK TX" },
	{ "LYON" },
	{ "MACON GA" },
	{ "MADISON WA" },
	{ "MADISON WI" },
	{ "MADRID" },
	{ "MANCHESTER NH" },
	{ "MANILA" },
	{ "MCALLEN TX" },
	{ "MCKINNEY TX" },
	{ "MELBOURNE" },
	{ "MEMPHIS TN" },
	{ "MESA AZ" },
	{ "MESQUITE TX" },
	{ "MEXICO CITY" },
	{ "MIAMI FL" },
	{ "MIAMI GARDENS FL" },
	{ "MIDLAND TX" },
	{ "MILAN" },
	{ "MILWAUKEE WA" },
	{ "MINNEAPOLIS MN" },
	{ "MIRAMAR FL" },
	{ "MOBILE AL" },
	{ "MODESTO CA" },
	{ "MONTERREY" },
	{ "MONTGOMERY AL" },
	{ "MONTGOMERY WV" },
	{ "MORENO VALLEY CA" },
	{ "MUMBAI" },
	{ "MUNICH" },
	{ "MURFREESBORO TN" },
	{ "MURRIETA CA" },
	{ "NAGOYA" },
	{ "NANCHANG" },
	{ "NANJING" },
	{ "NAPERVILLE IL" },
	{ "NASHVILLE TN" },
	{ "NEW DELHI" },
	{ "NEW HAVEN CT" },
	{ "NEW ORLEANS LA" },
	{ "NEW YORK NY" },
	{ "NEWARK NJ" },
	{ "NEWPORT NEWS VA" },
	{ "NICE" },
	{ "NORFOLK VA" },
	{ "NORMAN OK" },
	{ "NORTH CHARLESTON SC" },
	{ "NORTH LAS VEGAS NV" },
	{ "NORWALK CA" },
	{ "OAKLAND CA" },
	{ "OCEANSIDE CA" },
	{ "ODESSA TX" },
	{ "OKLAHOMA CITY OK" },
	{ "OLATHE KS" },
	{ "OMAHA NE" },
	{ "ONTARIO CA" },
	{ "ORANGE CA" },
	{ "ORLANDO FL" },
	{ "OSAKA" },
	{ "OVERLAND PARK KS" },
	{ "OXNARD CA" },
	{ "PALM BAY FL" },
	{ "PALMDALE CA" },
	{ "PARIS" },
	{ "PASADENA CA" },
	{ "PASADENA TX" },
	{ "PATERSON NJ" },
	{ "PEARLAND TX" },
	{ "PEMBROKE PINES FL" },
	{ "PEORIA AZ" },
	{ "PEORIA IL" },
	{ "PHILADELPHIA PA" },
	{ "PHOENIX AZ" },
	{ "PITTSBURGH PA" },
	{ "PLANO TX" },
	{ "POMONA CA" },
	{ "POMPANO BEACH FL" },
	{ "PORT ST LUCIE FL" },
	{ "PORTLAND OR" },
	{ "PROVIDENCE RI" },
	{ "PROVO UT" },
	{ "PUEBLO CO" },
	{ "PUNE" },
	{ "QINGDAO" },
	{ "RALEIGH NC" },
	{ "RANCHO CUCAMONGA CA" },
	{ "RARITAN NJ" },
	{ "RENO NV" },
	{ "RHINE RUHR" },
	{ "RIALTO CA" },
	{ "RICHARDSON TX" },
	{ "RICHMOND CA" },
	{ "RICHMOND VA" },
	{ "RIO DE JANEIRO" },
	{ "RIVERSIDE CA" },
	{ "ROCHESTER MN" },
	{ "ROCHESTER NY" },
	{ "ROCKFORD IL" },
	{ "ROME" },
	{ "ROSEVILLE CA" },
	{ "ROUND ROCK TX" },
	{ "S CHARLESTON WV" },
	{ "SACRAMENTO CA" },
	{ "SALEM OR" },
	{ "SALINAS CA" },
	{ "SALT LAKE CITY UT" },
	{ "SAN ANTONIO TX" },
	{ "SAN BERNARDINO CA" },
	{ "SAN DIEGO CA" },
	{ "SAN FRANCISCO CA" },
	{ "SAN JOSE CA" },
	{ "SAN MATEO CA" },
	{ "SANDY SPRINGS GA" },
	{ "SANTA ANA CA" },
	{ "SANTA CLARA CA" },
	{ "SANTA CLARITA CA" },
	{ "SANTA MARIA CA" },
	{ "SANTA ROSA CA" },
	{ "SANTIAGO" },
	{ "SAO PAULO" },
	{ "SAVANNAH GA" },
	{ "SCOTTSDALE AZ" },
	{ "SEATTLE WA" },
	{ "SEOUL" },
	{ "SHANGHAI" },
	{ "SHENYANG" },
	{ "SHENZHEN" },
	{ "SHREVEPORT LA" },
	{ "SIMI VALLEY CA" },
	{ "SIOUX FALLS SD" },
	{ "SOUTH BEND IN" },
	{ "SPOKANE WA" },
	{ "SPRING HILL WV" },
	{ "SPRINGFIELD IL" },
	{ "SPRINGFIELD MA" },
	{ "SPRINGFIELD MO" },
	{ "ST LOUIS MO" },
	{ "ST PAUL MN" },
	{ "ST PETERSBURG FL" },
	{ "STAMFORD CT" },
	{ "STERLING HEIGHTS MI" },
	{ "STOCKTON CA" },
	{ "STUTTGART" },
	{ "SUNNYVALE CA" },
	{ "SURAT" },
	{ "SURPRISE AZ" },
	{ "SYDNEY" },
	{ "SYRACUSE NY" },
	{ "TACOMA WA" },
	{ "TAIPEI" },
	{ "TALLAHASSEE FL" },
	{ "TAMPA FL" },
	{ "TEHRAN" },
	{ "TEMECULA CA" },
	{ "TEMPE AZ" },
	{ "THORNTON CO" },
	{ "THOUSAND OAKS CA" },
	{ "TIANJIN" },
	{ "TOKYO" },
	{ "TOLEDO OH" },
	{ "TOPEKA KS" },
	{ "TORONTO" },
	{ "TORRANCE CA" },
	{ "TUCSON AZ" },
	{ "TULSA OK" },
	{ "TYLER TX" },
	{ "VALLEJO CA" },
	{ "VANCOUVER WA" },
	{ "VENTURA CA" },
	{ "VICTORVILLE CA" },
	{ "VIRGINIA BEACH VA" },
	{ "VISALIA CA" },
	{ "W COVINA CA" },
	{ "W JORDAN UT" },
	{ "W PALM BEACH FL" },
	{ "W VALLEY CITY UT" },
	{ "WACO TX" },
	{ "WARREN MI" },
	{ "WASHINGTON DC" },
	{ "WATERBURY CT" },
	{ "WENZHOU" },
	{ "WESTMINSTER CO" },
	{ "WICHITA KS" },
	{ "WICHITA FALLS TX" },
	{ "WILMINGTON NC" },
	{ "WINSTON NC" },
	{ "WINSTON SALEM NC" },
	{ "WORCESTER MA" },
	{ "WUHAN" },
	{ "XIAN" },
	{ "YONKERS NY" },
	{ "ZHENGZHOU" },
	{ "ZURICH" }
};

// QSO parts

const BHMorse::qsoPart_t BHMorse::_QSOParts[] PROGMEM =
{
	{" TNX FER CALL"},		// FB1
	{" FB"},							// FB2
	{" FB OM"},						// FB3
	{" R R"},							// FB4
	{""},									// FB5

	{" DE "},							// DE

	{" = UR RST IS "},		// RST1
	{" = RST "},					// RST2

	{" = MY NAME IS "},		// Name1
	{" = NAME HR IS "},		// Name2
	{" = NAME IS "},			// Name3
	{" = NAME "},					// Name4

	{" = QTH IS "},				// QTH1
	{" = QTH "},					// QTH2

	{" = HW CPY? "},			// Bk2U1
	{" = BK TO U "},			// Bk2U2
	{" = "},							// Bk2U3

	{" K "},							// K1
	{" ("}								// K2 {KN}
};

// temporary buffer for building messages

char _tmpBuffer[BHMORSE_MESSAGE_BUFRSIZE];

//////////////////////////////////////////////////////////////////////////////
// Character map
//////////////////////////////////////////////////////////////////////////////

const BHMorse::charElement_t BHMorse::_charElemMap[] PROGMEM =
{
	{BHMORSE_CHAR_ELEMENT_MAP_DIFFICULTY_SPACE,  7, 0x00000000}, // inter-character space
	{7, 19, 0xEBAEE000}, // !
	{6, 15, 0xBABA0000}, // "
	{5, 15, 0xABAE0000}, // # {SK}
	{7, 17, 0xABAB8000}, // $
	{7, 11, 0xABA00000}, // % {SN}
	{8, 15, 0xEBAE0000}, // & {CT}/{KA} start of message
	{7, 19, 0xBBBBA000}, // '
	{5, 15, 0xEBBA0000}, // ( also {KN}
	{7, 19, 0xEBBAE000}, // )
	{6, 11, 0xBAE00000}, // * {AA} new line
	{7, 13, 0xBAE80000}, // + also {AR} new page
	{5, 19, 0xEEAEE000}, // ,
	{7, 15, 0xEAAE0000}, // -
	{5, 17, 0xBAEB8000}, // .
	{5, 13, 0xEAE80000}, // /
	{4, 19, 0xEEEEE000}, // 0
	{4, 17, 0xBBBB8000}, // 1
	{4, 15, 0xAEEE0000}, // 2
	{4, 13, 0xABB80000}, // 3
	{4, 11, 0xAAE00000}, // 4
	{4,  9, 0xAA800000}, // 5
	{4, 11, 0xEAA00000}, // 6
	{4, 13, 0xEEA80000}, // 7
	{4, 15, 0xEEEA0000}, // 8
	{4, 17, 0xEEEE8000}, // 9
	{7, 17, 0xEEEA8000}, // :
	{7, 17, 0xEBAE8000}, // ;
	BHMORSE_CHAR_ELEMENT_MAP_UNUSED, // < UNUSED
	{5, 13, 0xEAB80000}, // =
	BHMORSE_CHAR_ELEMENT_MAP_UNUSED, // > UNUSED
	{5, 15, 0xAEEA0000}, // ?
	{6, 17, 0xBBAE8000}, // @
	{1,  5, 0xB8000000}, // A
	{3,  9, 0xEA800000}, // B
	{3, 11, 0xEBA00000}, // C
	{2,  7, 0xEA000000}, // D
	{1,  1, 0x80000000}, // E
	{3,  9, 0xAE800000}, // F
	{2,  9, 0xEE800000}, // G
	{2,  7, 0xAA000000}, // H
	{1,  3, 0xA0000000}, // I
	{3, 13, 0xBBB80000}, // J
	{2,  9, 0xEB800000}, // K
	{3,  9, 0xBA800000}, // L
	{1,  7, 0xEE000000}, // M
	{1,  5, 0xE8000000}, // N
	{2, 11, 0xEEE00000}, // O
	{3, 11, 0xBBA00000}, // P
	{3, 13, 0xEEB80000}, // Q
	{2,  7, 0xBA000000}, // R
	{1,  5, 0xA8000000}, // S
	{1,  3, 0xE0000000}, // T
	{2,  7, 0xAE000000}, // U
	{3,  9, 0xAB800000}, // V
	{2,  9, 0xBB800000}, // W
	{3, 11, 0xEAE00000}, // X
	{3, 13, 0xEBB80000}, // Y
	{3, 11, 0xEEA00000}, // Z
	BHMORSE_CHAR_ELEMENT_MAP_UNUSED, // [ UNUSED
	{6, 23, 0xABBBAA00}, // "\" {SOS}
	BHMORSE_CHAR_ELEMENT_MAP_UNUSED, // ] UNUSED
	{3, 15, 0xAAAA0000}, // ^ {HH} error
	{7, 17, 0xAEEB8000}, // _
	{5, 11, 0xBAA00000}  // ` {AS} wait
};

void BHMorse::getRandomName(char* retV)
{
	// return a random name from the table in PROGMEM

	int r = random(0, BH_ARRAY_SIZE(_firstNames));

	firstName_t buffer;
	memcpy_P(&buffer, &_firstNames[r], sizeof(buffer));
	strcpy(retV, buffer.d);
}

void BHMorse::getRandomCity(char* retV)
{
	// return a random city from the table in PROGMEM

	int r = random(0, BH_ARRAY_SIZE(_cities));

	city_t buffer;
	memcpy_P(&buffer, &_cities[r], sizeof(buffer));
	strcpy(retV, buffer.d);
}

void BHMorse::getRandomCall(char* retV)
{
	// return a random callsign
	//
	// 1-2 letters
	// 1 number
	// 1-3 letters (but fix A1B to A1BC or A1BCD)

	byte n;		// # of times
	byte p;		// random char
	byte l;		// length

	// empty

	strcpy(retV, "");

	// prefix

	n = random(1, 3);
	for (byte i = 0; i < n; i++)
	{
		p = random(BHMORSE_PREFIX_MIN, BHMORSE_PREFIX_MAX + 1);
		l = strlen(retV);
		retV[l] = p;
		retV[l + 1] = BH_END_OF_STRING;
	}

	// number

	p = random(BHMORSE_NUMBER_MIN, BHMORSE_NUMBER_MAX + 1);
	l = strlen(retV);
	retV[l] = p;
	retV[l + 1] = BH_END_OF_STRING;

	// suffix

	n = random(4 - strlen(retV), 4);	// if "A1" so far, force suffix to >= 2 chars
	for (byte i = 0; i < n; i++)
	{
		p = random(BHMORSE_SUFFIX_MIN, BHMORSE_SUFFIX_MAX + 1);
		l = strlen(retV);
		retV[l] = p;
		retV[l + 1] = BH_END_OF_STRING;
	}
}

void BHMorse::getRandomRST(char* retV)
{
	// random RST
	//
	// R = [3-5]
	// S = [4-9]
	// T = [7-9]

	strcpy(retV, "");
	retV[0] = random(BHMORSE_RST_R_MIN, BHMORSE_RST_R_MAX + 1);
	retV[1] = random(BHMORSE_RST_S_MIN, BHMORSE_RST_S_MAX + 1);
	retV[2] = random(BHMORSE_RST_T_MIN, BHMORSE_RST_T_MAX + 1);
	retV[3] = BH_END_OF_STRING;
}

BHMorse::charElement_t BHMorse::getCharElement(int p)
{
	// read a character definition from PROGMEM

	charElement_t retV;
	memcpy_P(&retV, &_charElemMap[p], sizeof(charElement_t));
	return retV;
}

void BHMorse::getQSOPart(char* retV, int p)
{
	// read a QSO part from PROGMEM

	qsoPart_t b;
	memcpy_P(&b, &_QSOParts[p], sizeof(qsoPart_t));
	strcpy(retV, b.d);
}

void BHMorse::redoCharDifficultyPtrs()
{
	// populate the table with pointers to all of the characters
	// in the current range of enabled difficulty

	_numCharDifficultyPtrs = 0;

	for (int i = 0; i < BH_ARRAY_SIZE(_charElemMap); i++)
	{
		charElement_t c = getCharElement(i);
		if (c.difficulty <= enabledDifficulty())
		{
			_ptrsToCharsWithEnabledDifficulty[_numCharDifficultyPtrs] = i;
			_numCharDifficultyPtrs++;
		}
	}
}

boolean BHMorse::isSpace(charElement_t pChar)
{
	// returns true if the passed character is a space

	return (pChar.difficulty == BHMORSE_CHAR_ELEMENT_MAP_DIFFICULTY_SPACE);
}

void BHMorse::loadChar()
{
	// load a copy of the next character to be sent

	_tempChar = BHMORSE_CHAR_ELEMENT_MAP_UNUSED;
	_numElemsInCharSent = 0;

	if (strlen(_message) > 0)
	{
		byte c = _message[_numCharsInMsgSent];
		int c2s = c - BHMORSE_CHAR_ELEMENT_MAP_OFFSET;

		// see if it's a valid index into the character map

		if ((c2s >= 0) &&
				(c2s < BH_ARRAY_SIZE(_charElemMap)))
		{
			_tempChar = getCharElement(c2s);
		}
	}
}

void BHMorse::loadNextChar()
{
	// load next random character to send no harder than enabled difficulty

	int rndChar = random(0, _numCharDifficultyPtrs);
	_tmpBuffer[0] = _ptrsToCharsWithEnabledDifficulty[rndChar] + BHMORSE_CHAR_ELEMENT_MAP_OFFSET;
	_tmpBuffer[1] = BH_END_OF_STRING;
	setMessage(_tmpBuffer);
}

void BHMorse::loadNextGroup()
{
	// load next group of random characters no harder than enabled difficulty

	byte rndNumChars = random(BHMORSE_RANDOMGROUP_MIN, BHMORSE_RANDOMGROUP_MAX + 1);
	byte rndChar;

	for (int i = 0; i < rndNumChars; i++)
	{
		rndChar = random(0, _numCharDifficultyPtrs);
		_tmpBuffer[i] = char(_ptrsToCharsWithEnabledDifficulty[rndChar] + BHMORSE_CHAR_ELEMENT_MAP_OFFSET);
	}
	_tmpBuffer[rndNumChars] = BH_END_OF_STRING;

	setMessage(_tmpBuffer);
}

void BHMorse::loadNextQSO()
{
	// load next random QSO

	char bufr[BHMORSE_CITY_MAXLEN];		// buffer large enough to hold largest part
	byte p;

	strcpy(_tmpBuffer, "");

	// get calls

	char callA[10];
	getRandomCall(callA);

	char callB[10];
	getRandomCall(callB);

	// calla DE callb

	strcpy(_tmpBuffer, callA);

	getQSOPart(bufr, QSOPart_Row::DE);
	strcat(_tmpBuffer, bufr);

	strcat(_tmpBuffer, callB);

	// FB

	p = random(QSOPart_Row::FB1, QSOPart_Row::FB5 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	// RST

	p = random(QSOPart_Row::RST1, QSOPart_Row::RST2 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	getRandomRST(bufr);
	strcat(_tmpBuffer, bufr);

	// Name

	p = random(QSOPart_Row::Name1, QSOPart_Row::Name4 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	getRandomName(bufr);
	strcat(_tmpBuffer, bufr);

	// QTH

	p = random(QSOPart_Row::QTH1, QSOPart_Row::QTH2 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	getRandomCity(bufr);
	strcat(_tmpBuffer, bufr);

	// Back to you

	p = random(QSOPart_Row::Bk2U1, QSOPart_Row::Bk2U3 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	// calla DE callb

	strcat(_tmpBuffer, callA);

	getQSOPart(bufr, QSOPart_Row::DE);
	strcat(_tmpBuffer, bufr);

	strcat(_tmpBuffer, callB);

	// K

	p = random(QSOPart_Row::K1, QSOPart_Row::K2 + 1);
	getQSOPart(bufr, p);
	strcat(_tmpBuffer, bufr);

	// send it

	setMessage(_tmpBuffer);
}

//////////////////////////////////////////////////////////////////////////////
// constructors
//////////////////////////////////////////////////////////////////////////////

BHMorse::BHMorse()
{
	// constructor
	// put stuff you don't want to do until main.setup() in begin()

	_ptrsToCharsWithEnabledDifficulty = new byte[BH_ARRAY_SIZE(_charElemMap)];

	// stop running

	_runMode = Idle;

	// reset some things

	_numCharDifficultyPtrs = 0;	// just in case
}

//////////////////////////////////////////////////////////////////////////////
// Morse parameter getters for backed properties
//////////////////////////////////////////////////////////////////////////////

BHMorse::wpmFactor_t BHMorse::wpmSchemeFactor()
{
	return _wpmSchemeFactor;
}

BHMorse::wpm_t BHMorse::overallSpeed()
{
	// this is "s" in the ARRL calculations

	return _overallSpeed;
}

BHMorse::wpm_t BHMorse::userCharSpeed()
{
	return _userCharSpeed;
}

BHMorse::difficulty_t BHMorse::enabledDifficulty()
{
	return _enabledDifficulty;
}

//////////////////////////////////////////////////////////////////////////////
// Morse parameter getters for computed properties
//////////////////////////////////////////////////////////////////////////////

BHMorse::wpm_t BHMorse::charSpeed()
{
	// the actual character (dit mark) speed that we'll use;
	// this is "c" in the ARRL calculations

	int retV = 0;

	if (overallSpeed() >= BHMORSE_FARNSWORTH_CAP)
	{
		retV = overallSpeed();
	}
	else
	{
		retV = max(userCharSpeed(), overallSpeed());
	}

	return retV;
}

BHMorse::duration_t BHMorse::charDitMarkTime()
{
	// the character speed dit mark time
	// this is "u" in ARRL calculations

	duration_t retV = 0;

	if (charSpeed() != 0)
	{
		retV = wpmSchemeFactor() / charSpeed();
	}

	return retV;
}

BHMorse::duration_t BHMorse::charDitSpaceTime()
{
	// the character dit space time;
	// we're at a fixed Weight of 0.50

	return charDitMarkTime();
}

BHMorse::duration_t BHMorse::charDahMarkTime()
{
	// the character dah mark time;
	// we're at a fixed Ratio of BHMORSE_DITS_PER_DAH

	return (charDitMarkTime() * BHMORSE_DITS_PER_DAH);
}

BHMorse::duration_t BHMorse::farnsworthDelayTime()
{
	// the Farnsworth delay factor;
	// this is t(a) in ARRL calculations

	double numerator = ((60.0 * charSpeed()) - (37.2 * overallSpeed())) * 1000;
	double denominator = (charSpeed() * overallSpeed());
	duration_t retV = numerator / denominator;

	return retV;
}

BHMorse::duration_t BHMorse::interCharSpaceTime()
{
	// the time between characters;
	// this is t(c) in ARRL calculations

	return ((BHMORSE_DITS_PER_DAH * farnsworthDelayTime()) / 19);
}

BHMorse::duration_t BHMorse::interWordSpaceTime()
{
	// the time between words:
	// this is t(w) in ARRL calculations

	return ((BHMORSE_DITS_PER_CHARSPACE * farnsworthDelayTime()) / 19);
}

//////////////////////////////////////////////////////////////////////////////
// Morse parameter setters
//////////////////////////////////////////////////////////////////////////////

void BHMorse::setWpmSchemeFactor(BHMorse::wpmFactor_t newValue)
{
	if (true)
	{
		_wpmSchemeFactor = newValue;
	}
}

void BHMorse::setOverallSpeed(BHMorse::wpm_t newValue)
{
	if ((newValue >= BHMORSE_MIN_WPM) &&
			(newValue <= BHMORSE_MAX_WPM))
	{
		_overallSpeed = newValue;
		saveOverallSpeed();
	}
}

void BHMorse::setUserCharSpeed(BHMorse::wpm_t newValue)
{
	if ((newValue >= BHMORSE_MIN_WPM) &&
			(newValue <= BHMORSE_MAX_WPM))
	{
		_userCharSpeed = newValue;
		saveUserCharSpeed();
	}
}

void BHMorse::setEnabledDifficulty(BHMorse::difficulty_t newValue)
{
	if ((newValue >= BHMORSE_MIN_CHARACTER_DIFFICULTY) &&
			(newValue <= BHMORSE_MAX_CHARACTER_DIFFICULTY))
	{
		_enabledDifficulty = newValue;
		saveEnabledDifficulty();
		redoCharDifficultyPtrs();
	}
}

//////////////////////////////////////////////////////////////////////////////
// sound parameter getters
//////////////////////////////////////////////////////////////////////////////

BH_pin_t BHMorse::tonePin()
{
	return _tonePin;
}

BHMorse::hz_t BHMorse::pitch()
{
	return _pitch;
}

//////////////////////////////////////////////////////////////////////////////
// sound parameter setters
//////////////////////////////////////////////////////////////////////////////

void BHMorse::setTonePin(BH_pin_t newValue)
{
	_tonePin = newValue;
	pinMode(_tonePin, OUTPUT);
	noTone(_tonePin);
}

void BHMorse::setPitch(BHMorse::hz_t newValue, bool pSave)
{
	if ((newValue >= BHMORSE_MIN_PITCH) &&
			(newValue <= BHMORSE_MAX_PITCH))
	{
		_pitch = newValue;
		if (pSave) savePitch();
	}
}

//////////////////////////////////////////////////////////////////////////////
// message parameter getters
//////////////////////////////////////////////////////////////////////////////

void BHMorse::message(char* retV)
{
	strcpy(retV, _message);
}

//////////////////////////////////////////////////////////////////////////////
// message parameter setters
//////////////////////////////////////////////////////////////////////////////

void BHMorse::setMessage(char const* newValue)
{
#ifdef BHMORSE_DEBUG
	if (strlen(newValue) > 0)
	{
		Serial.print(F("Message = '"));
		Serial.print(newValue);
		Serial.println(F("'"));
	}
#endif

	strcpy(_message, newValue);

	// load 1st character

	_numCharsInMsgSent = 0;
	
	loadChar();
}

//////////////////////////////////////////////////////////////////////////////
// other getters
//////////////////////////////////////////////////////////////////////////////

BHMorse::RunMode BHMorse::runMode()
{
	return _runMode;
}

//////////////////////////////////////////////////////////////////////////////
// other setters
//////////////////////////////////////////////////////////////////////////////

void BHMorse::setRunMode(BHMorse::RunMode newValue)
{
	_runMode = newValue;

	setMessage("");

	// if it's one of the random run modes, prime the first message

	switch (runMode())
	{
		case Idle:
			break;

		case SendChars:
			loadNextChar();
			break;

		case SendGroups:
			loadNextGroup();
			break;

		case SendQSOs:
			loadNextQSO();
			break;

		default:
			break;
	}
}

//////////////////////////////////////////////////////////////////////////////
// EEPROM settings stuff
//////////////////////////////////////////////////////////////////////////////

BHMorse::eepromSignature_t BHMorse::readSignature()
{
	// read signature

	BHMorse::eepromSignature_t es = 0;
	EEPROM.get(BHMORSE_EEPROM_ADDR_SIGNATURE, es);

	return es;
}

void BHMorse::readOverallSpeed()
{
	// read signature

	BHMorse::wpm_t tmpWpm;
	EEPROM.get(BHMORSE_EEPROM_ADDR_OVERALLSPEED, tmpWpm);
	setOverallSpeed(tmpWpm);
}

void BHMorse::readUserCharSpeed()
{
	// read user character speed

	BHMorse::wpm_t tmpWpm;
	EEPROM.get(BHMORSE_EEPROM_ADDR_USERCHARSPEED, tmpWpm);
	setUserCharSpeed(tmpWpm);
}

void BHMorse::readEnabledDifficulty()
{
	// read enabled difficulty

	BHMorse::difficulty_t tmpDifficulty;
	EEPROM.get(BHMORSE_EEPROM_ADDR_HIGHESTENABLEDDIFFICULTY, tmpDifficulty);
	setEnabledDifficulty(tmpDifficulty);
}

void BHMorse::readPitch()
{
	// read pitch

	BHMorse::hz_t tmpHz;
	EEPROM.get(BHMORSE_EEPROM_ADDR_PITCH, tmpHz);
	setPitch(tmpHz, true);
}

void BHMorse::loadSettings()
{
	// read persistent settings from EEPROM

	if (readSignature() == BHMORSE_EEPROM_SIGNATURE_V1)
	{
		// get settings from EEPROM

		readOverallSpeed();
		readUserCharSpeed();
		readEnabledDifficulty();
		readPitch();
	}
	else
	{
		// new defaults

		resetSettings();
	}
}

void BHMorse::resetSettings()
{
	// reset settings to factory defaults

	saveSignature();
	setOverallSpeed(BHMORSE_DEFAULT_OVERALLSPEED);
	setUserCharSpeed(BHMORSE_DEFAULT_USERCHARSPEED);
	setEnabledDifficulty(BHMORSE_DEFAULT_ENABLEDDIFFICULTY);
	setPitch(BHMORSE_DEFAULT_PITCH, true);
}

void BHMorse::saveSignature()
{
	BHMorse::eepromSignature_t es = BHMORSE_EEPROM_SIGNATURE_V1;
	EEPROM.put(BHMORSE_EEPROM_ADDR_SIGNATURE, es);
	delay(BHMORSE_EEPROM_WRITE_DELAY);
}

void BHMorse::saveOverallSpeed()
{
	EEPROM.put(BHMORSE_EEPROM_ADDR_OVERALLSPEED, _overallSpeed);
	delay(BHMORSE_EEPROM_WRITE_DELAY);
}

void BHMorse::saveUserCharSpeed()
{
	EEPROM.put(BHMORSE_EEPROM_ADDR_USERCHARSPEED, _userCharSpeed);
	delay(BHMORSE_EEPROM_WRITE_DELAY);
}

void BHMorse::saveEnabledDifficulty()
{
	EEPROM.put(BHMORSE_EEPROM_ADDR_HIGHESTENABLEDDIFFICULTY, _enabledDifficulty);
	delay(BHMORSE_EEPROM_WRITE_DELAY);
}

void BHMorse::savePitch()
{
	EEPROM.put(BHMORSE_EEPROM_ADDR_PITCH, _pitch);
	delay(BHMORSE_EEPROM_WRITE_DELAY);
}

//////////////////////////////////////////////////////////////////////////////
// other methods
//////////////////////////////////////////////////////////////////////////////

void BHMorse::begin(BH_pin_t tonePin)
{
	// do stuff that you can't or don't want to do in the constructor

	// seed the "random" # generator

	randomSeed(analogRead(BHMORSE_UNUSED_ANALOGPIN));

	// load settings from EEPROM

	loadSettings();

	// set WPM Factor

	setWpmSchemeFactor(BHMORSE_WPMSCHEMEFACTOR_PARIS);

	// install parameters

	setTonePin(tonePin);
}

boolean BHMorse::elemsRemainInChar()
{
	// returns true if any elements remain to be sent in the current character

	return (_numElemsInCharSent < _tempChar.numElems);
}

boolean BHMorse::charsRemainInMsg()
{
	// returns true if any characters remain to be sent in the message

	return (_numCharsInMsgSent < strlen(_message));
}

boolean BHMorse::msgDone()
{
	// returns true if any elements remain to be sent in the current character,
	// or any characters remain to be sent in the message

	return (!elemsRemainInChar() && !charsRemainInMsg());
}

void BHMorse::sendUntilMsgDone()
{
	// send elements until the message is done

	while (!msgDone())
	{
		sendNextElem();
	}
}

void BHMorse::sendMessage(const char* pMessage)
{
  // send a message and wait for it to finish

  setRunMode(SendMessage);
  setMessage(pMessage);
  sendUntilMsgDone();
}

void BHMorse::sendNextElem()
{
	// send the next element to be sent
	// [this requires the bit after the last used bit to still be 0]

	if (bitRead(_tempChar.elements, (BHMORSE_CHAR_ELEMENT_MAP_HIELEMENTBIT - _numElemsInCharSent)))
	{
		bool offAfter =
		(bitRead(_tempChar.elements,
						 (BHMORSE_CHAR_ELEMENT_MAP_HIELEMENTBIT - 1 - _numElemsInCharSent)) == 0);

		sendMark(offAfter);
	}
	else
	{
		sendSpace();
	}

	// bump element counter

	_numElemsInCharSent++;

	if (!elemsRemainInChar())
	{
		// character's finished

		// bump character counter

		_numCharsInMsgSent++;

		if (charsRemainInMsg())
		{
			// get next character

			loadChar();

			// only if the next char isn't a space, wait inter-character space,
			// so we don't add inter-char space to inter-word space

			if (!isSpace(_tempChar))
			{
				waitInterCharSpace();
			}
		}
		else
		{
			// message is finished
			// see if I need to load the next message

			switch (runMode())
			{
				case Idle:
					// weird; I shouldn't be here
					break;

				case SendMessage:
					// wait a little
					waitInterCharSpace();
					// go idle
					setRunMode(Idle);
					break;

				case SendChars:
					// wait a little
					waitInterCharSpace();
					// load next character
					loadNextChar();
					break;

				case SendGroups:
					// wait
					waitInterWordSpace();
					// load next group
					loadNextGroup();
					break;

				case SendQSOs:
					// wait
					waitInterWordSpace();
					waitInterWordSpace();
					// load next QSO
					loadNextQSO();
					break;

				case SendFile:
					// nothing to do next; go idle
					setRunMode(Idle);

				default:
					// weird; I shouldn't be here
					setRunMode(Idle);
					break;
			}
		}
	}
}

void BHMorse::sendMark(bool pStopAfter)
{
	// send an element of mark

	tone(tonePin(), pitch());
	delay(charDitMarkTime());
	if (pStopAfter) noTone(tonePin());
}

void BHMorse::sendSpace()
{
	// send an element of space

	noTone(tonePin());
	waitInterElemSpace();
}

void BHMorse::waitInterElemSpace()
{
	// wait the time between elements

	delay(charDitSpaceTime());
}

void BHMorse::waitInterCharSpace()
{
	// wait the time between characters

	delay(interCharSpaceTime());
}

void BHMorse::waitInterWordSpace()
{
	// wait the time between words

	delay(interWordSpaceTime());
}
