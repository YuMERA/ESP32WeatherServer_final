const char index_html[] PROGMEM = R"=====(
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
            <meta http-equiv="refresh" content="300">
            <title>Weather station by me[R]a</title>
            <link rel="preconnect" href="https://fonts.gstatic.com"><link href="https://fonts.googleapis.com/css2?family=Oswald:wght@600&family=Roboto&display=swap" rel="stylesheet">
            <link rel="stylesheet" href="style.css">
            <!-- <link rel="shortcut icon" type="image/ico" href="favicon1.ico"/> -->
            <link href="https://websygen.github.io/owfont/css/owfont-regular.css" rel="stylesheet" type="text/css"/>
            <link href="data:image/x-icon;base64,
                        AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAAAAgAAAAAAAAAAAAAAAEAAAAAAAAAAAAAAANwD/
                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEREAAAAAEREREQAA
                        AAARERERAAAAABEREREAAAAAEREREQAAAAARERERAAAAABEREREAARAAEREREQAREQARERERAREREBERERERERERERER
                        EREREREREREREREREREREREREAEREREREREAABEREREREAAAAREREREAAAAAEREP8AAAD/AAAA/wAAAP8AAAD/AAAA/w
                        AAAOcAAADDAAAAgQAAAAAAAAAAAAAAAAAAABgAAAA8AAAAfgAAAP8AAA" rel="icon" type="image/x-icon" />
        </head>
        <body>
            <div class='container'>
                <header>
                    <h2 style='font-size: 1.5rem;'>ESP Weather station by <span style='color:#F36454;font-weight:bold'>me[R]a</span></h2>
                    <h3 style='color:#b8b5b3'>M.Gorkog 82, naselje Istok, Šid</h3>
                    
                    <ul class="menu">
                        <li><a href="/"><span style="color: #eb6206;"> Home </span></a></li>
                        <li><a href="gra.html"> Graph </a></li>
                        <li><a href="min.html"> Min View </a></li>
                        <li><a href="json.html" target='_blank' title='Data podaci u Json formatu'> Json </a></li>
                        <li><a href="map.html"> Location </a></li>
                        <li><a href="about.html"> About</a></li>
                    </ul>
                </header>
                <nav>
                    <div class="widgets">
                        <div class="w-header">
                            <i class='owf owf-@@w_icon@@ owf-4x owf-pull-left ' style="color:black; float: right;"></i>
                            <p>&nbsp</p>
                            <h3> Šid, RS
                             <!-- zastava srbije -->
                             <img src="data:image/png;base64,
                             iVBORw0KGgoAAAANSUhEUgAAABAAAAALCAIAAAD5gJpuAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5cc
                             llPAAAAUlJREFUeNp0UE1Lw0AQnW02AcVcRPyoWqnYnHvy6FVRf4GIR/+BHoI3wb9RRKFXERSP1aMgCIWCVARRlKKh
                             lTQimp1xNpuEgvjYHWZm572ZHfEMgMlRmTMYwp+8eAQY294AIj5IpAiUdgCTENNkmnmtn8iYRZA+mw/M7qAcXysqpL
                             fLDzfq6j6kYbQdb5at1B0J4yRrjQy7O/MA1GncmExaPeBLr+Qvzi1df3eBVLAM7dUaq5b93dHai9blUYGn1d+pzri3
                             xZLkgBQCKnbkxGTl/BTi+KfVAjLroIwDkFyZNORqTXhvXEXHdW7tFKcAykY4JWQQURTlQXNlvXKwzwJ3/l714owy6L
                             0gOo7T6/VEv98XQhjCV/v+6fAIFU5vbQ55C6bUVLO1LCsMQ8Ek27ZhAHobiHlo/EKhwFYTgiDABOYtn+E//AowAFh4
                             /jzczTSYAAAAAElFTkSuQmCC">
                             </h3>
                            <p>&nbsp;@@w_sta@@ - @@w_stas@@</p>
                            
                        </div>
                        <div class="w-content">
                            <div class="left-w-content">
                                <p>@@w_temhead@@°C</p>
                            </div>
                            <div class="right-w-content">
                                <p style="margin: 0 0 5px 3px;"><b>Details</b></p><hr>
                                <table style="width: 100%;">
                                    <tr><td>Temp</td><td><b>@@w_tem@@°C</b></td></tr>
                                    <tr><td>Pressure</td><td><b>@@w_pre@@ hPa</b></td></tr>
                                    <tr><td>Humidity</td><td><b>@@w_hum@@ %</b></td></tr>
                                    <tr><td>UV Index</td><td><b>@@w_uvi@@</b></td></tr>
                                    <tr><td>Altitude</td><td><b>@@w_alt@@ m</b></td></tr>
                                </table>
                            </div>
                        </div>
                        <p style="font-size: 14px;text-align: center; padding: 5px;"><b>Air Quality - @@w_air@@</b></p>
                        <div class="w-footer">
                            <iframe src="https://free.timeanddate.com/clock/i7teai0k/n3395/tlrs36/tct/pct/tt0/tw0/tm1/ts1" frameborder="0" width="125" height="18" allowtransparency="true"></iframe>
                        </div>
                    </div>
                    <br>
                    
                    <div class="trenutno-stanje">
                        <p>Latitude: <b>@@n_lat@@°N</b></p>
                        <p>Longitude: <b>@@n_lon@@°E</b></p>
                        <p>Sunrise (izlazak sunca) : <b>@@n_izl@@</b></p>
                        <p>Sunset (zalazak sunca) : <b>@@n_zal@@</b></p><br>
                    </div>
                    <div class="klimerko">
                        <a href='https://klimerko.org/' target='_blank' title='Vazduh građanima'>Klimerko</a>
                        <p style='margin: 20px 30px 5px 0px;'>Air Quality <br>(<em>kvalitet vazduha</em>)</p><hr>
                        <p style='color: @@k_color@@; margin: 5px 0 5px 0;'><strong>@@k_air@@ (<em>@@k_airs@@</em>)</strong></p>
                        
                        <table style="width: 45%;margin: 5px 0px; padding: 3px;">
                            <tr><td>PM1</td><td style="text-align: right;"><b>@@k_pm0@@ µg/m³</b></td></tr>
                            <tr><td>PM2.5</td><td style="text-align: right;"><b>@@k_pm2@@ µg/m³</b></td></tr>
                            <tr><td>PM10</td><td style="text-align: right;"><b>@@k_pm1@@ µg/m³</b></td></tr>
                        </table>
                        <hr>
                        <p style="margin: 5px 0px; font-size: 11px;">Zadnje merenje : @@k_last@@</p>
                        <br>
                        <p style="text-align: right;">Your IP : @@ip@@</p>
                    </div>
                </nav>             
            
                <article>
                    <table>
                        <tr><th>Measured <i>(Izmereno)</i></th><th>Value <i>(Vrednost)</i></th><th>Unit <i>(Jedinica)</i></th></tr>
                        <tr><td><b>Temperature</b> (<i>Temperatura): </i></td><td style="font-weight: bold;" id='Tem'>@@h_tem@@</td><td>°C</td></tr>
                        <tr><td><b>Humidity</b> (<i>Vlažnost): <i></td><td style="font-weight: bold;" id='Hum'>@@h_hum@@</td><td>% RH</td></tr>
                        <tr><td><b>Atmospheric pressure</b> (<i>Atmosferski pritisak</i>): </td><td style="font-weight: bold;" id='Pre'>@@h_pre@@</td><td>hPa</td></tr>
                        <tr><td><b>PM1</b> (<i>Suspendovane čestice</i>): </td><td style="font-weight: bold;" id='Pre'>@@h_pm0@@</td><td>µg/m³</td></tr>
                        <tr><td><b>PM2.5</b> (<i>Suspendovane čestice</i>): </td><td style="font-weight: bold;" id='Pre'>@@h_pm1@@</td><td>µg/m³</td></tr>
                        <tr><td><b>PM10</b> (<i>Suspendovane čestice</i>): </td><td style="font-weight: bold;" id='Pre'>@@h_pm2@@</td><td>µg/m³</td></tr>    
                        <tr><td><b>Wind speed</b> (<i>Brzina vetra</i>): </td><td style="font-weight: bold;" id='Win1'>@@h_winsm@@</td><td>m/s</td></tr>
                        <tr><td><b>Wind direction</b> (<i>Smer vetra</i>): </td><td style="font-weight: bold;" id='wind_deg'>@@h_wins@@</td><td id='symbolWindDir'>@@h_wind@@</td></tr>
                        <tr><td><b>Cloudiness</b> (<i>Oblačnost</i>): </td><td style="font-weight: bold;">@@h_obl@@</td><td>%</td></tr>
                        <tr><td><b>Sunrise</b> (<i>Izlazak sunca</i>): </td><td style="font-weight: bold;">@@h_izl@@</td><td>-</td></tr>
                        <tr><td><b>Sunset</b> (<i>Zalazak sunca</i>): </td><td style="font-weight: bold;">@@h_zal@@</td><td>-</td></tr>
                        <tr><td><b>UV index</b> (<i>UV index</i>): </td><td style="font-weight: bold;" id='uv_index'>@@h_uv@@</td><td>@@h_uvd@@</td></tr>
                        <tr><td><b>Altitude</b> (<i>Apsolutna visina</i>): </td><td style="font-weight: bold;">@@h_alt@@</td><td>m</td></tr>
                        <tr><td><b>VCC Battery</b> (<i>Napon baterije</i>): </td><td style="font-weight: bold;" id='Vcc'>@@h_vcc@@</td><td>V</td></tr>
                        <tr><td><b>RSSI</b> (<i>Jačina WiFi signala</i>): </td><td style="font-weight: bold;" id='Rsi'>@@h_rsi@@</td><td>dBm</td></tr>
                        <tr><th colspan="3" style="font-size: 12px; text-align: left; padding: 5px;color: #333;">Last measurement (<em>Zadnje merenje</em>): @@h_mes@@<br>
                            <marquee>The measurement is repeated every 10 minutes (<em>Merenje se ponavlja svakih 10 minuta</em>).</marquee></th></tr>
                    </table>
                    
                    <center><br>
                        <div class="flag-counter" style="position: relative; padding: 5px;">
                            <a href="https://www.flagcounter.me/details/bY2"><img src="https://www.flagcounter.me/bY2/" alt="Flag Counter"></a>
                        </div>
                    </center>
                                 
                </article> 
                
            </div>

            <center>
                <footer>
                    <h4>Copyright &copy; me[R]a</h4>
                    <p>Automatic meteo station with solar panel and lithium-ion battery in test procedure 
                        (Automatska meteo stanica sa solarnim panelom i litijum-jonskom baterijom u postupku testiranja).</p>
                </footer>
            </center>
        </body>
    </html>
)=====";

const char about_html[] PROGMEM = R"=====(
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
            <title>Weather station by me[R]a</title>
            <link rel="stylesheet" href="style.css">
            <!-- <link rel="shortcut icon" type="image/ico" href="favicon1.ico"/> -->
            <link href="https://websygen.github.io/owfont/css/owfont-regular.css" rel="stylesheet" type="text/css"/>
            <link href="data:image/x-icon;base64,
                        AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAAAAgAAAAAAAAAAAAAAAEAAAAAAAAAAAAAAANwD/
                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEREAAAAAEREREQAA
                        AAARERERAAAAABEREREAAAAAEREREQAAAAARERERAAAAABEREREAARAAEREREQAREQARERERAREREBERERERERERERER
                        EREREREREREREREREREREREREAEREREREREAABEREREREAAAAREREREAAAAAEREP8AAAD/AAAA/wAAAP8AAAD/AAAA/w
                        AAAOcAAADDAAAAgQAAAAAAAAAAAAAAAAAAABgAAAA8AAAAfgAAAP8AAA" rel="icon" type="image/x-icon" />
            <style>
                .about-title {margin: 30px; text-align: center;}
                .about-title h1 {font-size: 36px; color: #eb6206;}
                .about-title h2 {font-size: 24px; font-style: oblique;}
                .text-box {max-width: 900px; margin: 30px; padding: 20px; border: 1px solid black; text-align: left;}
                .text-box p {font-size: 16px; text-align:left;letter-spacing: 0px;}
            </style>
            
        </head>
        <body>
            <div class='container'>
                <header>
                    <h2 style='font-size: 1.5rem;'>ESP Weather station by <span style='color:#eb6206;font-weight:bold'>me[R]a</span></h2>
                    <h3 style='color:#b8b5b3'>M.Gorkog 82, naselje Istok, Šid</h3>
                    <ul class="menu">
                        <li><a href="/"> Home </a></li>
                        <li><a href="gra.html"> Graph </a></li>
                        <li><a href="min.html"> Min View </a></li>
                        <li><a href="json.html" target='_blank' title='Data podaci u Json formatu'> Json </a></li>
                        <li><a href="map.html"> Location </a></li>
                        <li><a href="about.html"><span style="color: #eb6206;"> About </span></a></li>
                    </ul>
                </header>
            </div>
            <div class="about-title">
                <h1>About Us</h1>
                <h2>Nešto o samoj meterološkoj stanici</h2>
            </div>
            <center><div class="text-box">
                <p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>DiY</b> meteorološka wifi stanica namenjena je za razna meteorološka merenja od kojih izdvajamo nekoliko glavnih a to su 
                    temperatura, vlažnost vazduha kao i vazdušni pritisak. Osim tih merenja ova stanica meri i kvalitet vazduha u vidu koncetracije suspenzovanih PM čestica i to PM1, PM2.5 i PM10
                     izražene u μg/m3. Postoji prikaz vrednosti brzine i smera vetra kao i UV index sunčevog zračenja.
                    <br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Večina podatak se očitava na samoj meteo stanici dok neki podaci se preuzimaju sa zvaničnih meteo stanica koje se nalaze u neposrednoj blizini moje
                     lokacije pa shodno tome mogu se smatrati validnim za moju poziciju. Neki od takvih preuzetih podataka su UV index, izlazak i zalazak sunca, trenutna 
                     oblačnost, vrsta i intezitet padavina ako trenutno postoje.
                    <br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Meteo stanica je <b>experimentalnog karaktera</b> i očitani podaci mogu da se smatraju poprilično tačnim ali nikako kao potpuno i precizno tačni za grad Šid, 
                     pogotovo što se stanica nalazi na periferiji grada u naselju Istok koje je visinski izdignuto u odnosu na centar grada i postoje razlike u intezitetu vetra
                     kao i temperaturna razlika.</p><br>

                <p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Tehničke karakteristike stanice joj omogućavaju potpunu energetsku nezavisnost kao i autonomnost jer poseduje mali solarni panel <em>(6V 150mA)</em> koji 
                     kontrolisano <em>(modul TP4056)</em> puni litium jonsku bateriju <em>(3.7V 2200mAh)</em> i tako omogućava neprekidan rad meteo stanice. 
                     <br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Centralna jedinica elektronike je <b>WiFi modul ESP8266</b> koji radi kao klijent i <b>svakih 10 minuta</b>, bežičnim putem, salje izmerene podatke
                     na drugi <b>ESP8266/ESP32</b> koji je web server i povezan je na kućni internet ruter preko wifi-a. Na taj način uvek preko interneta je dostupan prikaz svih izmerenih i preuzetih
                     meteoroloških podataka bez dodatne opreme kao sto je računar ili sl. 
                     <br><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Prilikom projektovanja elektronike kao i softvera vodilo se računa o što manjoj potrošnji struje kako bi baterija bila uvek puna i 
                     spremna za rad i u noćnim uslovima kao i u uslovima oblačnosti gde solarni panel ne proizvodi struju.
                     Kao što sam napomenuo, stanica je u eksperimentalnoj fazi razvoja a konačne zamisli se dopunjavaju postepeno kad dozvoli slobodno vreme i finansije.</p>
                <br>    
                <p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;me[R]a</p>
            </div></center>
        
            <center>
                <footer>
                    <h4>Copyright &copy; me[R]a</h4>
                    <p>Automatic meteo station with solar panel and lithium-ion battery in test procedure 
                        (Automatska meteo stanica sa solarnim panelom i litijum-jonskom baterijom u postupku testiranja).</p>
                </footer>
            </center>

        </body>
    </html>
)=====";

const char json_html[] PROGMEM = R"=====(
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
            <title>Weather station by me[R]a - Json Data</title>
            <link href="data:image/x-icon;base64,
                        AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAAAAgAAAAAAAAAAAAAAAEAAAAAAAAAAAAAAANwD/
                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEREAAAAAEREREQAA
                        AAARERERAAAAABEREREAAAAAEREREQAAAAARERERAAAAABEREREAARAAEREREQAREQARERERAREREBERERERERERERER
                        EREREREREREREREREREREREREAEREREREREAABEREREREAAAAREREREAAAAAEREP8AAAD/AAAA/wAAAP8AAAD/AAAA/w
                        AAAOcAAADDAAAAgQAAAAAAAAAAAAAAAAAAABgAAAA8AAAAfgAAAP8AAA" rel="icon" type="image/x-icon" />
        </head>
        <body>
            Nije implementirano!
        </body>

    </html>
)=====";

const char min_html[] PROGMEM = R"=====(
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
            <title>Weather station by me[R]a</title>
            <link rel="stylesheet" href="style.css">
            <!-- <link rel="shortcut icon" type="image/ico" href="favicon1.ico"/> -->
            <link href="https://websygen.github.io/owfont/css/owfont-regular.css" rel="stylesheet" type="text/css"/>
            <link href="data:image/x-icon;base64,
                        AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAAAAgAAAAAAAAAAAAAAAEAAAAAAAAAAAAAAANwD/
                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEREAAAAAEREREQAA
                        AAARERERAAAAABEREREAAAAAEREREQAAAAARERERAAAAABEREREAARAAEREREQAREQARERERAREREBERERERERERERER
                        EREREREREREREREREREREREREAEREREREREAABEREREREAAAAREREREAAAAAEREP8AAAD/AAAA/wAAAP8AAAD/AAAA/w
                        AAAOcAAADDAAAAgQAAAAAAAAAAAAAAAAAAABgAAAA8AAAAfgAAAP8AAA" rel="icon" type="image/x-icon" />
            <link href='https://fonts.googleapis.com/css?family=Open+Sans:300,400,600' rel='stylesheet'>
            <style>
                html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #444444;}
                body{margin: 0px;} 
                h1 {margin: 50px auto 30px;} 
                .side-by-side{display: table-cell;vertical-align: middle;position: relative;}
                .text{font-weight: 600;font-size: 19px;width: 200px;}
                .reading{font-weight: 300;font-size: 50px;padding-right: 25px;}
                .temperature .reading{color: #F29C1F;}
                .humidity .reading{color: #3B97D3;}
                .pressure .reading{color: #26B99A;}
                .altitude .reading{color: #955BA5;}
                .superscript{font-size: 17px;font-weight: 600;position: absolute;top: 10px;}
                .data{padding: 10px;}
                .min{display: table;margin: 150px auto 200px;}
                .icon{width:65px}
            </style>
        </head>
        <body>
            <div class='container'>
                <header>
                    <h2 style='font-size: 1.5rem;'>ESP Weather station by <span style='color:#eb6206;font-weight:bold'>me[R]a</span></h2>
                    <h3 style='color:#b8b5b3'>M.Gorkog 82, naselje Istok, Šid</h3>
                    <ul class="menu">
                        <li><a href="/"> Home </a></li>
                        <li><a href="gra.html"> Graph </a></li>
                        <li><a href="min.html"><span style="color: #eb6206;"> Min View </span></a></li>
                        <li><a href="json.html" target='_blank' title='Data podaci u Json formatu'> Json </a></li>
                        <li><a href="map.html"> Location </a></li>
                        <li><a href="about.html"> About </a></li>
                    </ul>
                </header>
            </div>
                <div class='min'>
                    <div class='data temperature'>
                        <div class='side-by-side icon'>
                            <svg enable-background='new 0 0 19.438 54.003'height=54.003px id=Layer_1 version=1.1 viewBox='0 0 19.438 54.003'width=19.438px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><g><path d='M11.976,8.82v-2h4.084V6.063C16.06,2.715,13.345,0,9.996,0H9.313C5.965,0,3.252,2.715,3.252,6.063v30.982
                            C1.261,38.825,0,41.403,0,44.286c0,5.367,4.351,9.718,9.719,9.718c5.368,0,9.719-4.351,9.719-9.718
                            c0-2.943-1.312-5.574-3.378-7.355V18.436h-3.914v-2h3.914v-2.808h-4.084v-2h4.084V8.82H11.976z M15.302,44.833
                            c0,3.083-2.5,5.583-5.583,5.583s-5.583-2.5-5.583-5.583c0-2.279,1.368-4.236,3.326-5.104V24.257C7.462,23.01,8.472,22,9.719,22
                            s2.257,1.01,2.257,2.257V39.73C13.934,40.597,15.302,42.554,15.302,44.833z'fill=#F29C21 /></g></svg>
                    </div>
                        <div class='side-by-side text'>Temperature</div>
                        <div class='side-by-side reading'>@@min-tem@@<span class='superscript'>°C</span></div>
                        </div>
                    <div class='data humidity'>
                        <div class='side-by-side icon'>
                            <svg enable-background='new 0 0 29.235 40.64'height=40.64px id=Layer_1 version=1.1 viewBox='0 0 29.235 40.64'width=29.235px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><path d='M14.618,0C14.618,0,0,17.95,0,26.022C0,34.096,6.544,40.64,14.618,40.64s14.617-6.544,14.617-14.617
                            C29.235,17.95,14.618,0,14.618,0z M13.667,37.135c-5.604,0-10.162-4.56-10.162-10.162c0-0.787,0.638-1.426,1.426-1.426
                            c0.787,0,1.425,0.639,1.425,1.426c0,4.031,3.28,7.312,7.311,7.312c0.787,0,1.425,0.638,1.425,1.425
                            C15.093,36.497,14.455,37.135,13.667,37.135z'fill=#3C97D3 /></svg>
                        </div>
                        <div class='side-by-side text'>Humidity</div>
                        <div class='side-by-side reading'>@@min-hum@@<span class='superscript'>%</span></div>
                    </div>
                    <div class='data pressure'>
                        <div class='side-by-side icon'>
                            <svg enable-background='new 0 0 40.542 40.541'height=40.541px id=Layer_1 version=1.1 viewBox='0 0 40.542 40.541'width=40.542px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><g><path d='M34.313,20.271c0-0.552,0.447-1,1-1h5.178c-0.236-4.841-2.163-9.228-5.214-12.593l-3.425,3.424
                            c-0.195,0.195-0.451,0.293-0.707,0.293s-0.512-0.098-0.707-0.293c-0.391-0.391-0.391-1.023,0-1.414l3.425-3.424
                            c-3.375-3.059-7.776-4.987-12.634-5.215c0.015,0.067,0.041,0.13,0.041,0.202v4.687c0,0.552-0.447,1-1,1s-1-0.448-1-1V0.25
                            c0-0.071,0.026-0.134,0.041-0.202C14.39,0.279,9.936,2.256,6.544,5.385l3.576,3.577c0.391,0.391,0.391,1.024,0,1.414
                            c-0.195,0.195-0.451,0.293-0.707,0.293s-0.512-0.098-0.707-0.293L5.142,6.812c-2.98,3.348-4.858,7.682-5.092,12.459h4.804
                            c0.552,0,1,0.448,1,1s-0.448,1-1,1H0.05c0.525,10.728,9.362,19.271,20.22,19.271c10.857,0,19.696-8.543,20.22-19.271h-5.178
                            C34.76,21.271,34.313,20.823,34.313,20.271z M23.084,22.037c-0.559,1.561-2.274,2.372-3.833,1.814
                            c-1.561-0.557-2.373-2.272-1.815-3.833c0.372-1.041,1.263-1.737,2.277-1.928L25.2,7.202L22.497,19.05
                            C23.196,19.843,23.464,20.973,23.084,22.037z'fill=#26B999 /></g></svg>
                        </div>
                        <div class='side-by-side text'>Pressure</div>
                        <div class='side-by-side reading'>@@min-pre@@<span class='superscript'>hPa</span></div>
                    </div>
                    <div class='data altitude'>
                        <div class='side-by-side icon'>
                            <svg enable-background='new 0 0 58.422 40.639'height=40.639px id=Layer_1 version=1.1 viewBox='0 0 58.422 40.639'width=58.422px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><g><path d='M58.203,37.754l0.007-0.004L42.09,9.935l-0.001,0.001c-0.356-0.543-0.969-0.902-1.667-0.902
                            c-0.655,0-1.231,0.32-1.595,0.808l-0.011-0.007l-0.039,0.067c-0.021,0.03-0.035,0.063-0.054,0.094L22.78,37.692l0.008,0.004
                            c-0.149,0.28-0.242,0.594-0.242,0.934c0,1.102,0.894,1.995,1.994,1.995v0.015h31.888c1.101,0,1.994-0.893,1.994-1.994
                            C58.422,38.323,58.339,38.024,58.203,37.754z'fill=#955BA5 /><path d='M19.704,38.674l-0.013-0.004l13.544-23.522L25.13,1.156l-0.002,0.001C24.671,0.459,23.885,0,22.985,0
                            c-0.84,0-1.582,0.41-2.051,1.038l-0.016-0.01L20.87,1.114c-0.025,0.039-0.046,0.082-0.068,0.124L0.299,36.851l0.013,0.004
                            C0.117,37.215,0,37.62,0,38.059c0,1.412,1.147,2.565,2.565,2.565v0.015h16.989c-0.091-0.256-0.149-0.526-0.149-0.813
                            C19.405,39.407,19.518,39.019,19.704,38.674z'fill=#955BA5 /></g></svg>
                        </div>
                        <div class='side-by-side text'>Altitude</div>
                        <div class='side-by-side reading'>@@min-alt@@<span class='superscript'>m</span></div>
                    </div>
                </div>

                <center>
                    <footer>
                        <h4>Copyright &copy; me[R]a</h4>
                        <p>Automatic meteo station with solar panel and lithium-ion battery in test procedure 
                            (Automatska meteo stanica sa solarnim panelom i litijum-jonskom baterijom u postupku testiranja).</p>
                    </footer>
                </center>
        </body>
    </html>
)=====";

const char map_html[] PROGMEM = R"=====(
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
            <title>Weather station by me[R]a</title>
            <link rel="stylesheet" href="style.css">
            <!-- <link rel="shortcut icon" type="image/ico" href="favicon1.ico"/> -->
            <link href="https://websygen.github.io/owfont/css/owfont-regular.css" rel="stylesheet" type="text/css"/>
            <link href="data:image/x-icon;base64,
                        AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAAAAgAAAAAAAAAAAAAAAEAAAAAAAAAAAAAAANwD/
                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEREAAAAAEREREQAA
                        AAARERERAAAAABEREREAAAAAEREREQAAAAARERERAAAAABEREREAARAAEREREQAREQARERERAREREBERERERERERERER
                        EREREREREREREREREREREREREAEREREREREAABEREREREAAAAREREREAAAAAEREP8AAAD/AAAA/wAAAP8AAAD/AAAA/w
                        AAAOcAAADDAAAAgQAAAAAAAAAAAAAAAAAAABgAAAA8AAAAfgAAAP8AAA" rel="icon" type="image/x-icon" />
        </head>
        <body>
            <div class='container'>
                <header>
                    <h2 style='font-size: 1.5rem;'>ESP Weather station by <span style='color:#eb6206;font-weight:bold'>me[R]a</span></h2>
                    <h3 style='color:#b8b5b3'>M.Gorkog 82, naselje Istok, Šid</h3>
                    <ul class="menu">
                        <li><a href="/"> Home </a></li>
                        <li><a href="gra.html"> Graph </a></li>
                        <li><a href="min.html"> Min View </a></li>
                        <li><a href="json.html" target='_blank' title='Data podaci u Json formatu'> Json </a></li>
                        <li><a href="map.html"><span style="color: #eb6206;"> Location </span></a></li>
                        <li><a href="about.html"> About </a></li>
                    </ul>
                </header>
            </div>
            <center><div class='mapouter'>
                <div class='gmap_canvas'>
                <iframe width='800' height='600' id='gmap_canvas' src='https://maps.google.com/maps?q=Meteo%20Stanica%20MERA&t=&z=15&ie=UTF8&iwloc=&output=embed' frameborder='0' scrolling='no' marginheight='0' marginwidth='0'></iframe>
                <a href='https://embedgooglemap.net/maps/36'></a>
                <br>
                <style>.mapouter{margin: 50px 0 70px; text-align:right;height:600px;width:800px;}</style>
                <a href='https://www.embedgooglemap.net'></a>
                <style>.gmap_canvas {overflow:hidden;background:none!important;height:600px;width:800px;}</style>
                </div>
            </div></center>
        
            <center>
                <footer>
                    <h4>Copyright &copy; me[R]a</h4>
                    <p>Automatic meteo station with solar panel and lithium-ion battery in test procedure 
                        (Automatska meteo stanica sa solarnim panelom i litijum-jonskom baterijom u postupku testiranja).</p>
                </footer>
            </center>
            
        </body>
    </html>
)=====";

const char gra_html[] PROGMEM = R"=====(
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
            <title>Weather station by me[R]a</title>
            <link rel="stylesheet" href="style.css">
            <!-- <link rel="shortcut icon" type="image/ico" href="favicon1.ico"/> -->
            <link href="https://websygen.github.io/owfont/css/owfont-regular.css" rel="stylesheet" type="text/css"/>
            <link href="data:image/x-icon;base64,
                        AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAAAAgAAAAAAAAAAAAAAAEAAAAAAAAAAAAAAANwD/
                        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEREAAAAAEREREQAA
                        AAARERERAAAAABEREREAAAAAEREREQAAAAARERERAAAAABEREREAARAAEREREQAREQARERERAREREBERERERERERERER
                        EREREREREREREREREREREREREAEREREREREAABEREREREAAAAREREREAAAAAEREP8AAAD/AAAA/wAAAP8AAAD/AAAA/w
                        AAAOcAAADDAAAAgQAAAAAAAAAAAAAAAAAAABgAAAA8AAAAfgAAAP8AAA" rel="icon" type="image/x-icon" />
        </head>
        <body>
            <div class='container'>
                <header>
                    <h2 style='font-size: 1.5rem;'>ESP Weather station by <span style='color:#eb6206;font-weight:bold'>me[R]a</span></h2>
                    <h3 style='color:#b8b5b3'>M.Gorkog 82, naselje Istok, Šid</h3>
                    <ul class="menu">
                        <li><a href="/"> Home </a></li>
                        <li><a href="gra.html"><span style="color: #eb6206;"> Graph </span></a></li>
                        <li><a href="min.html"> Min View </a></li>
                        <li><a href="json.html" target='_blank' title='Data podaci u Json formatu'> Json </a></li>
                        <li><a href="map.html"> Location </a></li>
                        <li><a href="about.html"> About </a></li>
                    </ul>
                </header>
            </div>
            <center><div class="graph" style="max-width: 920px; min-width: 910px; text-align: left; margin: 10px;">
                <h2 style="text-align: center;">Grafički prikaz izmerenih vrednosti</h2>
                <h4 style="margin-bottom: 3px;">Powered by <span><a style="text-decoration: none; color:#eb6206;" href="https://thingspeak.com/" target='_blank'>ThingSpeak</a></span></h4>

                <iframe width='450' height='260' style='border: 1px solid #cccccc;' src='https://thingspeak.com/channels/1365442/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Temperature&type=line&yaxis=%C2%B0C'></iframe>
                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1365442/widgets/300750"></iframe>

                <iframe width='450' height='260' style='border: 1px solid #cccccc;' src='https://thingspeak.com/channels/1365442/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Atmospheric+pressure&type=line&yaxis=hPa'></iframe>
                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1365442/widgets/300762"></iframe>

                <iframe width='450' height='260' style='border: 1px solid #cccccc;' src='https://thingspeak.com/channels/1365442/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Humidity&type=line&yaxis=%25'></iframe>
                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1365442/widgets/300774"></iframe>

                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1365442/charts/5?bgcolor=%23ffffff&color=%23d62020&days=10&dynamic=true&results=2400&title=UV+index&type=line"></iframe>
                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1365442/widgets/312757"></iframe>

                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1365442/charts/7?bgcolor=%23ffffff&color=%23d62020&days=2&dynamic=true&results=60&title=RSSI&type=line&yaxis=dBm"></iframe>
                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1365442/widgets/300785"></iframe>

                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1365442/charts/6?bgcolor=%23ffffff&color=%23d62020&days=10&dynamic=true&results=2400&title=VCC+Battery&type=line&yaxis=V"></iframe>
                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1365442/widgets/300776"></iframe>

                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/apps/matlab_visualizations/405512"></iframe>

            </div></center>

            <center>
                <footer>
                    <h4>Copyright &copy; me[R]a</h4>
                    <p>Automatic meteo station with solar panel and lithium-ion battery in test procedure 
                        (Automatska meteo stanica sa solarnim panelom i litijum-jonskom baterijom u postupku testiranja).</p>
                </footer>
            </center> 
        
        </body>
    </html>
)=====";
