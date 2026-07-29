// ═══════════════════════════════════════════════════════════════
//    This arduino  A1 (TX)       ──→  (RX)
//    Semaphore Arduino pin 13 (TX) ──→  (RX)
//    GND ──────────────────────────── GND
//
//  Cascade Logic 
//    Only HC4               → AUTO:8
//    HC4 + HC3              → AUTO:10
//    HC4 + HC3 + HC2        → AUTO:12
//    HC4 + HC3 + HC2 + HC1  → AUTO:14
//    No one active          → RESET
//
//  WEB SERVER:
//    Browser → 192.168.100.120
// ═══════════════════════════════════════════════════════════════

#include <WiFiS3.h>
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>

// ── WiFi  ─────────────────────────────────────────
const char* SSID     = "YOUR_SSID";
const char* PASSWORD = "YOUR_PASSWORD";

// ── HTML in PROGMEM ────────────────────────────────────────────
const char HTML_PAGE[] PROGMEM =
  "<!DOCTYPE html>\n"
  "<html lang=\"sr\">\n"
  "<head>\n"
  "<meta charset=\"UTF-8\">\n"
  "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\n"
  "<title>SILS</title>\n"
  "<style>\n"
  "@import url('https://fonts.googleapis.com/css2?family=Syne:wght@700;800&family=DM+Mono:wght@400;500&display=swap');\n"
  ":root{\n"
  "  --bg:#0e1117;--bg2:#151a22;--bg3:#1c2330;\n"
  "  --ink:#e8e4de;--ink2:#9aa5b4;--ink3:#4a5568;\n"
  "  --amber:#f5a535;--amber2:#ffc46b;--amberd:rgba(245,165,53,0.15);\n"
  "  --green:#34d399;--red:#f87171;\n"
  "  --teal:#22d3ee;--teald:rgba(34,211,238,0.12);\n"
  "  --rule:rgba(255,255,255,0.07);--rule2:rgba(255,255,255,0.04);\n"
  "}\n"
  "body.light{\n"
  "  --bg:#f0ede8;--bg2:#e8e4de;--bg3:#ddd9d2;\n"
  "  --ink:#1a1714;--ink2:#3d3830;--ink3:#8a8278;\n"
  "  --rule:rgba(26,23,20,0.12);--rule2:rgba(26,23,20,0.06);\n"
  "  --amber:#e8820c;--amber2:#f5a535;--amberd:rgba(232,130,12,0.1);\n"
  "  --green:#1a7a4a;--red:#c0392b;\n"
  "  --teal:#0891b2;--teald:rgba(8,145,178,0.08);\n"
  "}\n"
  "*{margin:0;padding:0;box-sizing:border-box}\n"
  "html,body{height:100%;overflow:hidden}\n"
  "body{background:var(--bg);color:var(--ink);font-family:'DM Mono',monospace;display:flex;flex-direction:column}\n"
  "/* HEADER */\n"
  "header{\n"
  "  flex-shrink:0;padding:8px 18px;\n"
  "  border-bottom:1px solid var(--rule);\n"
  "  background:var(--bg2);\n"
  "  display:grid;grid-template-columns:auto 1fr auto;\n"
  "  align-items:center;gap:16px;\n"
  "}\n"
  ".h-left{display:flex;align-items:center;gap:10px}\n"
  ".h-logo{font-family:'Syne',sans-serif;font-size:11px;font-weight:800;letter-spacing:4px;text-transform:uppercase}\n"
  ".h-badge{font-size:8px;letter-spacing:2px;padding:2px 7px;border:1px solid var(--rule);color:var(--ink3);text-transform:uppercase;border-radius:2px}\n"
  ".h-status{display:flex;align-items:center;gap:5px;font-size:9px;letter-spacing:2px;text-transform:uppercase;color:var(--green)}\n"
  ".dot{width:5px;height:5px;border-radius:50%;background:var(--green);animation:blink 2s ease-in-out infinite;flex-shrink:0}\n"
  ".dot.off{background:var(--red);animation:none}\n"
  "@keyframes blink{0%,100%{opacity:1}50%{opacity:.3}}\n"
  ".h-center{text-align:center}\n"
  ".h-center h1{font-family:'Syne',sans-serif;font-size:12px;font-weight:800;letter-spacing:4px;text-transform:uppercase}\n"
  ".h-center p{font-size:8px;letter-spacing:2px;color:var(--ink3);margin-top:1px;text-transform:uppercase}\n"
  ".h-right{display:flex;align-items:center;justify-content:flex-end;gap:14px}\n"
  ".hstat .l{font-size:7px;letter-spacing:2px;color:var(--ink3);text-transform:uppercase;display:block}\n"
  ".hstat .v{font-size:12px;font-weight:500}\n"
  ".thbtn{font-family:'DM Mono',monospace;font-size:8px;letter-spacing:2px;text-transform:uppercase;padding:4px 9px;border:1px solid var(--rule);background:var(--bg3);color:var(--ink3);cursor:pointer;border-radius:2px}\n"
  "/* LAYOUT: senzori | centar | uart+log */\n"
  ".layout{\n"
  "  flex:1;min-height:0;\n"
  "  display:grid;\n"
  "  grid-template-columns:190px 1fr 220px;\n"
  "}\n"
  "/* LEFT SENSORS */\n"
  ".sensors{border-right:1px solid var(--rule);display:flex;flex-direction:column;overflow:hidden}\n"
  ".ptitle{padding:9px 14px 7px;border-bottom:1px solid var(--rule);font-size:8px;letter-spacing:3px;text-transform:uppercase;color:var(--ink3);display:flex;align-items:center;justify-content:space-between;flex-shrink:0}\n"
  ".ptitle-n{font-family:'Syne',sans-serif;font-size:15px;font-weight:800;color:var(--ink);letter-spacing:0}\n"
  ".slist{flex:1;overflow-y:auto;scrollbar-width:none}\n"
  ".slist::-webkit-scrollbar{display:none}\n"
  ".sc{padding:11px 14px;border-bottom:1px solid var(--rule2);position:relative;transition:background .3s}\n"
  ".sc.on{background:var(--amberd)}\n"
  ".sc.on::before{content:'';position:absolute;left:0;top:0;bottom:0;width:2px;background:var(--amber)}\n"
  ".sc-top{display:flex;justify-content:space-between;align-items:center;margin-bottom:6px}\n"
  ".sc-name{font-family:'Syne',sans-serif;font-size:10px;font-weight:700;letter-spacing:1px}\n"
  ".sc-tag{font-size:7px;letter-spacing:1px;padding:2px 5px;border:1px solid var(--rule);color:var(--ink3);text-transform:uppercase;transition:all .3s}\n"
  ".sc.on .sc-tag{border-color:var(--amber);color:var(--amber);background:var(--amberd)}\n"
  ".sc-d{font-family:'Syne',sans-serif;font-size:24px;font-weight:800;line-height:1;transition:color .3s}\n"
  ".sc.on .sc-d{color:var(--amber)}\n"
  ".sc-u{font-size:9px;color:var(--ink3);letter-spacing:1px;margin-left:2px}\n"
  ".sc-bar{height:2px;background:var(--rule);margin-top:7px;position:relative;overflow:visible}\n"
  ".sc-fill{height:100%;background:var(--ink3);transition:width .4s,background .3s}\n"
  ".sc.on .sc-fill{background:var(--amber)}\n"
  ".sc-thr{position:absolute;top:-3px;left:30%;width:1px;height:8px;background:var(--red);opacity:.5}\n"
  ".sc-sub{margin-top:5px;font-size:7px;color:var(--ink3);letter-spacing:1px}\n"
  "/* CENTER */\n"
  ".center{display:flex;flex-direction:column;overflow:hidden;border-right:1px solid var(--rule)}\n"
  "/* Street viz */\n"
  ".viz{flex-shrink:0;padding:14px 20px 10px;border-bottom:1px solid var(--rule)}\n"
  ".vlbl{font-size:8px;letter-spacing:3px;text-transform:uppercase;color:var(--ink3);margin-bottom:10px}\n"
  ".scene{position:relative;height:140px}\n"
  ".road{position:absolute;left:0;right:0;top:50%;transform:translateY(-50%);height:52px;background:#1a2235;border-radius:3px;border:1px solid var(--rule)}\n"
  ".roadl{position:absolute;top:50%;transform:translateY(-50%);left:0;right:0;height:2px;background:repeating-linear-gradient(90deg,rgba(245,165,53,.2) 0,rgba(245,165,53,.2) 20px,transparent 20px,transparent 40px)}\n"
  ".lamps{position:absolute;left:0;right:0;top:0;bottom:0;display:flex;justify-content:space-between;padding:0 24px;pointer-events:none}\n"
  ".lamp{display:flex;flex-direction:column;align-items:center;padding-top:4px}\n"
  ".lp{width:2px;height:60px;background:var(--bg3);position:relative}\n"
  ".la{position:absolute;top:0;width:16px;height:2px;background:var(--bg3);right:0}\n"
  ".lb{width:10px;height:10px;border-radius:50%;background:var(--ink3);border:1px solid var(--rule);position:absolute;top:-4px;right:-4px;transition:background .4s,box-shadow .4s}\n"
  ".lg{position:absolute;top:-18px;right:-20px;width:44px;height:34px;border-radius:50%;background:radial-gradient(ellipse,rgba(245,165,53,.55) 0,transparent 70%);opacity:0;transition:opacity .4s}\n"
  ".lamp.on .lb{background:var(--amber2);box-shadow:0 0 8px 3px rgba(245,165,53,.75)}\n"
  ".lamp.on .lg{opacity:1}\n"
  ".lb{background:#2a3545}\n"
  ".lamp.dim .lb{background:#3a4d2a;box-shadow:0 0 4px 1px rgba(245,165,53,.2)}\n"
  ".ln{font-size:7px;letter-spacing:1px;color:var(--ink3);margin-top:3px}\n"
  ".smark{position:absolute;top:50%;transform:translateY(-50%);width:26px;height:26px;border:1.5px solid rgba(255,255,255,.1);border-radius:3px;display:flex;align-items:center;justify-content:center;font-size:7px;color:rgba(255,255,255,.2);font-family:'DM Mono',monospace;transition:all .3s;margin-left:-13px}\n"
  ".smark.on{border-color:var(--amber);color:var(--amber);background:var(--amberd);box-shadow:0 0 10px rgba(245,165,53,.3)}\n"
  "#sm1{left:6%}#sm2{left:37%}#sm3{left:63%}#sm4{left:94%}\n"
  "/* Chart */\n"
  ".chart-area{flex:1;padding:12px 20px;display:flex;flex-direction:column;min-height:0}\n"
  ".chart-head{display:flex;justify-content:space-between;align-items:center;margin-bottom:8px;flex-shrink:0}\n"
  ".chart-ttl{font-size:8px;letter-spacing:3px;text-transform:uppercase;color:var(--ink3)}\n"
  ".chart-leg{display:flex;gap:12px}\n"
  ".cli{display:flex;align-items:center;gap:4px;font-size:8px;letter-spacing:1px;color:var(--ink3)}\n"
  ".cld{width:8px;height:2px;border-radius:1px}\n"
  ".chart-wrap{flex:1;position:relative;min-height:0}\n"
  "canvas{width:100%!important;height:100%!important}\n"
  "/* RIGHT: UART + LOG */\n"
  ".right{display:flex;flex-direction:column;overflow:hidden}\n"
  ".uart{flex-shrink:0}\n"
  ".uart-h{padding:9px 14px 7px;border-bottom:1px solid var(--rule);display:flex;align-items:center;justify-content:space-between}\n"
  ".uart-t{font-size:8px;letter-spacing:3px;text-transform:uppercase;color:var(--ink3)}\n"
  ".uart-b{font-size:8px;letter-spacing:1px;color:var(--ink3);background:var(--rule2);padding:2px 6px;border:1px solid var(--rule);border-radius:1px}\n"
  ".uart-last{padding:10px 14px;border-bottom:1px solid var(--rule2)}\n"
  ".ulbl{font-size:7px;letter-spacing:2px;text-transform:uppercase;color:var(--ink3);margin-bottom:4px}\n"
  ".umsg{font-family:'Syne',sans-serif;font-size:14px;font-weight:700;min-height:20px;color:var(--ink)}\n"
  ".umsg.auto{color:var(--green)}.umsg.rst{color:var(--ink3)}\n"
  ".uart-stats{display:grid;grid-template-columns:1fr 1fr;border-bottom:1px solid var(--rule2)}\n"
  ".us{padding:8px 14px;border-right:1px solid var(--rule2)}\n"
  ".us:last-child{border-right:none}\n"
  ".usl{font-size:7px;letter-spacing:2px;text-transform:uppercase;color:var(--ink3);display:block;margin-bottom:2px}\n"
  ".usv{font-family:'Syne',sans-serif;font-size:17px;font-weight:800;line-height:1;color:var(--ink)}\n"
  ".cascade-wrap{padding:9px 14px;border-bottom:1px solid var(--rule2)}\n"
  ".csc-row{display:flex;align-items:baseline;gap:4px;margin-top:3px}\n"
  ".csc-big{font-family:'Syne',sans-serif;font-size:28px;font-weight:800;line-height:1;color:var(--amber)}\n"
  ".csc-unit{font-size:9px;color:var(--ink3);letter-spacing:1px}\n"
  ".cbadges{margin-top:5px;display:flex;gap:4px;flex-wrap:wrap}\n"
  ".cbadge{font-size:7px;letter-spacing:2px;padding:2px 5px;border:1px solid var(--amber);color:var(--amber);text-transform:uppercase;border-radius:1px}\n"
  "/* ── TEMPERATURA ─────────────────────────────── */\n"
  ".temp-wrap{padding:10px 14px 12px;border-bottom:1px solid var(--rule2);position:relative;overflow:hidden}\n"
  ".temp-wrap::before{content:'';position:absolute;inset:0;background:var(--teald);opacity:0;transition:opacity .6s;pointer-events:none}\n"
  ".temp-wrap.hot::before{opacity:1}\n"
  ".temp-row{display:flex;align-items:center;gap:8px;margin-top:6px}\n"
  ".therm-svg{flex-shrink:0}\n"
  ".temp-vals{flex:1}\n"
  ".temp-big{font-family:'Syne',sans-serif;font-size:28px;font-weight:800;line-height:1;color:var(--teal);transition:color .6s;letter-spacing:-1px}\n"
  ".temp-unit{font-size:9px;color:var(--ink3);letter-spacing:1px;margin-top:1px}\n"
  ".temp-badge{display:inline-block;margin-top:4px;font-size:7px;letter-spacing:2px;padding:2px 6px;border:1px solid var(--teal);color:var(--teal);text-transform:uppercase;border-radius:1px;transition:all .6s}\n"
  ".temp-badge.warm{border-color:#f5a535;color:#f5a535}\n"
  ".temp-badge.hot{border-color:#f87171;color:#f87171}\n"
  ".temp-bar-col{display:flex;flex-direction:column;align-items:center;gap:2px}\n"
  ".temp-bar-wrap{position:relative;width:6px;height:48px;background:var(--rule);border-radius:3px;overflow:hidden}\n"
  ".temp-bar-fill{position:absolute;bottom:0;left:0;width:100%;background:linear-gradient(to top,var(--teal),#60a5fa);border-radius:3px;transition:height .9s cubic-bezier(.34,1.56,.64,1);height:0%}\n"
  ".temp-bar-lbl{font-size:6px;color:var(--ink3);letter-spacing:.5px}\n"
  "/* Termometar SVG animacija */\n"
  "@keyframes pulse-teal{0%,100%{opacity:1}50%{opacity:.55}}\n"
  ".therm-active #thbulb{animation:pulse-teal 1.8s ease-in-out infinite}\n"
  "/* LOG */\n"
  ".log-sec{flex:1;display:flex;flex-direction:column;overflow:hidden;min-height:0}\n"
  ".log-h{padding:9px 14px 7px;border-bottom:1px solid var(--rule);flex-shrink:0;font-size:8px;letter-spacing:3px;text-transform:uppercase;color:var(--ink3);display:flex;align-items:center;justify-content:space-between}\n"
  ".log-cnt{font-family:'Syne',sans-serif;font-size:13px;font-weight:700;color:var(--ink);letter-spacing:0}\n"
  ".log-body{flex:1;overflow-y:auto;min-height:0;scrollbar-width:thin;scrollbar-color:var(--rule) transparent}\n"
  ".log-body::-webkit-scrollbar{width:3px}\n"
  ".log-body::-webkit-scrollbar-thumb{background:var(--rule)}\n"
  ".le{padding:3px 14px;display:grid;grid-template-columns:44px 1fr;gap:6px;border-bottom:1px solid var(--rule2)}\n"
  ".lt{font-size:8px;color:var(--ink3);padding-top:1px}\n"
  ".lm{font-size:9px;color:var(--ink2);line-height:1.5}\n"
  ".lm.tx{color:var(--green)}.lm.sys{color:var(--amber)}.lm.ok{color:var(--green)}.lm.temp{color:var(--teal)}\n"
  "/* BOTTOM BAR */\n"
  ".bottom{flex-shrink:0;border-top:1px solid var(--rule);background:var(--bg2);display:grid;grid-template-columns:repeat(5,1fr)}\n"
  ".bc{padding:7px 14px;border-right:1px solid var(--rule);display:flex;flex-direction:column;justify-content:center}\n"
  ".bc:last-child{border-right:none}\n"
  ".bclbl{font-size:7px;letter-spacing:2px;text-transform:uppercase;color:var(--ink3);margin-bottom:2px}\n"
  ".bcv{font-family:'Syne',sans-serif;font-size:12px;font-weight:700;letter-spacing:.5px;line-height:1;color:var(--ink)}\n"
  ".bcv.ok{color:var(--green)}.bcv.warn{color:var(--amber)}.bcv.teal{color:var(--teal)}\n"
  ".pips{display:flex;gap:4px;align-items:center}\n"
  ".pip{width:8px;height:8px;border-radius:50%;border:1.5px solid var(--rule);background:var(--bg);transition:all .3s}\n"
  ".pip.on{background:var(--amber2);border-color:var(--amber);box-shadow:0 0 4px rgba(245,165,53,.6)}\n"
  "@media(max-width:860px){\n"
  "  html,body{height:auto;overflow:auto}\n"
  "  .layout{grid-template-columns:1fr;display:flex;flex-direction:column}\n"
  "  .sensors,.right{max-height:none}\n"
  "  .center{border-right:none}\n"
  "  .chart-wrap{min-height:180px}\n"
  "  .scene{height:100px}\n"
  "  header{grid-template-columns:1fr;gap:6px}\n"
  "  .h-right{flex-wrap:wrap;gap:8px;justify-content:flex-start}\n"
  "  .log-body{max-height:180px}\n"
  "}\n"
  "</style>\n"
  "</head>\n"
  "<body>\n"
  "<header>\n"
  "  <div class=\"h-left\">\n"
  "    <span class=\"h-logo\">SILS&#8209;NODE&#8209;01</span>\n"
  "    <span class=\"h-badge\">R4 WIFI</span>\n"
  "    <span class=\"h-status\"><span class=\"dot\" id=\"cdot\"></span><span id=\"ctxt\">ONLINE</span></span>\n"
  "  </div>\n"
  "  <div class=\"h-center\">\n"
  "    <h1>Smart Street Lighting System</h1>\n"
  "    <p>Arduino Uno R4 WiFi &nbsp;&#47;&#47;&nbsp; Live Monitor</p>\n"
  "  </div>\n"
  "  <div class=\"h-right\">\n"
  "    <div class=\"hstat\"><span class=\"l\">Vreme</span><span class=\"v\" id=\"clk\">--:--:--</span></div>\n"
  "    <div class=\"hstat\"><span class=\"l\">Uptime</span><span class=\"v\" id=\"upt\">00:00:00</span></div>\n"
  "    <div class=\"hstat\"><span class=\"l\">IP</span><span class=\"v\">192.168.100.120</span></div>\n"
  "    <button class=\"thbtn\" id=\"thbtn\" onclick=\"toggleTheme()\">&#9788; LIGHT</button>\n"
  "  </div>\n"
  "</header>\n"
  "\n"
  "<div class=\"layout\">\n"
  "  <!-- LEFT: SENSORS -->\n"
  "  <div class=\"sensors\">\n"
  "    <div class=\"ptitle\"><span>Senzori</span><span class=\"ptitle-n\" id=\"acnt\">0</span></div>\n"
  "    <div class=\"slist\">\n"
  "      <div class=\"sc\" id=\"sc1\">\n"
  "        <div class=\"sc-top\"><span class=\"sc-name\">HC&#8209;SR04 #1</span><span class=\"sc-tag\" id=\"t1\">SLOBODAN</span></div>\n"
  "        <div><span class=\"sc-d\" id=\"v1\">&#8212;</span><span class=\"sc-u\">cm</span></div>\n"
  "        <div class=\"sc-bar\"><div class=\"sc-fill\" id=\"b1\" style=\"width:0%\"></div><div class=\"sc-thr\"></div></div>\n"
  "        <div class=\"sc-sub\">PRAG 12cm</div>\n"
  "      </div>\n"
  "      <div class=\"sc\" id=\"sc2\">\n"
  "        <div class=\"sc-top\"><span class=\"sc-name\">HC&#8209;SR04 #2</span><span class=\"sc-tag\" id=\"t2\">SLOBODAN</span></div>\n"
  "        <div><span class=\"sc-d\" id=\"v2\">&#8212;</span><span class=\"sc-u\">cm</span></div>\n"
  "        <div class=\"sc-bar\"><div class=\"sc-fill\" id=\"b2\" style=\"width:0%\"></div><div class=\"sc-thr\"></div></div>\n"
  "        <div class=\"sc-sub\">PRAG 12cm</div>\n"
  "      </div>\n"
  "      <div class=\"sc\" id=\"sc3\">\n"
  "        <div class=\"sc-top\"><span class=\"sc-name\">HC&#8209;SR04 #3</span><span class=\"sc-tag\" id=\"t3\">SLOBODAN</span></div>\n"
  "        <div><span class=\"sc-d\" id=\"v3\">&#8212;</span><span class=\"sc-u\">cm</span></div>\n"
  "        <div class=\"sc-bar\"><div class=\"sc-fill\" id=\"b3\" style=\"width:0%\"></div><div class=\"sc-thr\"></div></div>\n"
  "        <div class=\"sc-sub\">PRAG 12cm</div>\n"
  "      </div>\n"
  "      <div class=\"sc\" id=\"sc4\">\n"
  "        <div class=\"sc-top\"><span class=\"sc-name\">HC&#8209;SR04 #4</span><span class=\"sc-tag\" id=\"t4\">SLOBODAN</span></div>\n"
  "        <div><span class=\"sc-d\" id=\"v4\">&#8212;</span><span class=\"sc-u\">cm</span></div>\n"
  "        <div class=\"sc-bar\"><div class=\"sc-fill\" id=\"b4\" style=\"width:0%\"></div><div class=\"sc-thr\"></div></div>\n"
  "        <div class=\"sc-sub\">PRAG 12cm</div>\n"
  "      </div>\n"
  "    </div>\n"
  "  </div>\n"
  "\n"
  "  <!-- CENTER: VIZ + CHART -->\n"
  "  <div class=\"center\">\n"
  "    <div class=\"viz\">\n"
  "      <div class=\"vlbl\">Vizualizacija ulice &mdash; Sektor A</div>\n"
  "      <div class=\"scene\">\n"
  "        <div class=\"road\"><div class=\"roadl\"></div></div>\n"
  "        <div class=\"smark\" id=\"sm1\">HC1</div>\n"
  "        <div class=\"smark\" id=\"sm2\">HC2</div>\n"
  "        <div class=\"smark\" id=\"sm3\">HC3</div>\n"
  "        <div class=\"smark\" id=\"sm4\">HC4</div>\n"
  "        <div class=\"lamps\">\n"
  "          <div class=\"lamp dim\" id=\"lp1\"><div class=\"lp\"><div class=\"la\"></div><div class=\"lg\"></div><div class=\"lb\"></div></div><span class=\"ln\">S1</span></div>\n"
  "          <div class=\"lamp dim\" id=\"lp2\"><div class=\"lp\"><div class=\"la\"></div><div class=\"lg\"></div><div class=\"lb\"></div></div><span class=\"ln\">S2</span></div>\n"
  "          <div class=\"lamp dim\" id=\"lp3\"><div class=\"lp\"><div class=\"la\"></div><div class=\"lg\"></div><div class=\"lb\"></div></div><span class=\"ln\">S3</span></div>\n"
  "          <div class=\"lamp dim\" id=\"lp4\"><div class=\"lp\"><div class=\"la\"></div><div class=\"lg\"></div><div class=\"lb\"></div></div><span class=\"ln\">S4</span></div>\n"
  "        </div>\n"
  "      </div>\n"
  "    </div>\n"
  "    <div class=\"chart-area\">\n"
  "      <div class=\"chart-head\">\n"
  "        <span class=\"chart-ttl\">Udaljenost senzora / 60s</span>\n"
  "        <div class=\"chart-leg\">\n"
  "          <div class=\"cli\"><div class=\"cld\" style=\"background:#f5a535\"></div>HC1</div>\n"
  "          <div class=\"cli\"><div class=\"cld\" style=\"background:#60a5fa\"></div>HC2</div>\n"
  "          <div class=\"cli\"><div class=\"cld\" style=\"background:#34d399\"></div>HC3</div>\n"
  "          <div class=\"cli\"><div class=\"cld\" style=\"background:#9aa5b4\"></div>HC4</div>\n"
  "        </div>\n"
  "      </div>\n"
  "      <div class=\"chart-wrap\"><canvas id=\"ch\"></canvas></div>\n"
  "    </div>\n"
  "  </div>\n"
  "\n"
  "  <!-- RIGHT: UART + LOG -->\n"
  "  <div class=\"right\">\n"
  "    <div class=\"uart\">\n"
  "      <div class=\"uart-h\"><span class=\"uart-t\">UART TX</span><span class=\"uart-b\">9600 BAUD</span></div>\n"
  "      <div class=\"uart-last\">\n"
  "        <div class=\"ulbl\">Poslednja komanda</div>\n"
  "        <div class=\"umsg rst\" id=\"umsg\">&#8212;</div>\n"
  "      </div>\n"
  "      <div class=\"uart-stats\">\n"
  "        <div class=\"us\"><span class=\"usl\">TX ukupno</span><span class=\"usv\" id=\"utx\">0</span></div>\n"
  "        <div class=\"us\"><span class=\"usl\">Mod</span><span class=\"usv\" id=\"umod\">&#8212;</span></div>\n"
  "      </div>\n"
  "      <div class=\"cascade-wrap\">\n"
  "        <div class=\"ulbl\">Kaskadno vreme semafora</div>\n"
  "        <div class=\"csc-row\"><span class=\"csc-big\" id=\"ctbig\">&#8212;</span><span class=\"csc-unit\">sek</span></div>\n"
  "        <div class=\"cbadges\" id=\"cbadges\"></div>\n"
  "      </div>\n"
  "      <!-- ── TEMPERATURA DHT ────────────────────── -->\n"
  "      <div class=\"temp-wrap\" id=\"tempwrap\">\n"
  "        <div class=\"ulbl\">Temperatura (DHT &mdash; klijent)</div>\n"
  "        <div class=\"temp-row\">\n"
  "          <svg class=\"therm-svg\" id=\"thermsvg\" width=\"28\" height=\"66\" viewBox=\"0 0 28 66\">\n"
  "            <!-- Tijelo termometra -->\n"
  "            <rect x=\"11.5\" y=\"2\" width=\"5\" height=\"40\" rx=\"2.5\" fill=\"none\" stroke=\"rgba(255,255,255,0.12)\" stroke-width=\"1\"/>\n"
  "            <!-- Fill - visina se mjenja JS-om -->\n"
  "            <rect id=\"thfill\" x=\"13\" y=\"42\" width=\"2\" height=\"0\" rx=\"1\" fill=\"#22d3ee\" style=\"transition:y .9s cubic-bezier(.34,1.56,.64,1),height .9s cubic-bezier(.34,1.56,.64,1)\"/>\n"
  "            <!-- Bulb outer ring -->\n"
  "            <circle cx=\"14\" cy=\"54\" r=\"8.5\" fill=\"none\" stroke=\"rgba(255,255,255,0.1)\" stroke-width=\"1\"/>\n"
  "            <!-- Bulb fill -->\n"
  "            <circle id=\"thbulb\" cx=\"14\" cy=\"54\" r=\"6.5\" fill=\"#22d3ee\" style=\"transition:fill .6s\"/>\n"
  "            <!-- Highlight -->\n"
  "            <circle cx=\"11.5\" cy=\"51.5\" r=\"1.5\" fill=\"rgba(255,255,255,0.3)\"/>\n"
  "            <!-- Skale (tick marks) -->\n"
  "            <line x1=\"16.5\" y1=\"8\"  x2=\"19\" y2=\"8\"  stroke=\"rgba(255,255,255,0.2)\" stroke-width=\"0.8\"/>\n"
  "            <line x1=\"16.5\" y1=\"18\" x2=\"19\" y2=\"18\" stroke=\"rgba(255,255,255,0.2)\" stroke-width=\"0.8\"/>\n"
  "            <line x1=\"16.5\" y1=\"28\" x2=\"19\" y2=\"28\" stroke=\"rgba(255,255,255,0.2)\" stroke-width=\"0.8\"/>\n"
  "            <line x1=\"16.5\" y1=\"38\" x2=\"19\" y2=\"38\" stroke=\"rgba(255,255,255,0.2)\" stroke-width=\"0.8\"/>\n"
  "          </svg>\n"
  "          <div class=\"temp-vals\">\n"
  "            <div class=\"temp-big\" id=\"tempbig\">&#8212;</div>\n"
  "            <div class=\"temp-unit\">&deg;C</div>\n"
  "            <div class=\"temp-badge\" id=\"tempbadge\">&#8212;</div>\n"
  "          </div>\n"
  "          <div class=\"temp-bar-col\">\n"
  "            <div class=\"temp-bar-lbl\">50</div>\n"
  "            <div class=\"temp-bar-wrap\"><div class=\"temp-bar-fill\" id=\"tempbar\"></div></div>\n"
  "            <div class=\"temp-bar-lbl\">0</div>\n"
  "          </div>\n"
  "        </div>\n"
  "      </div>\n"
  "    </div>\n"
  "    <div class=\"log-sec\">\n"
  "      <div class=\"log-h\"><span>Log</span><span class=\"log-cnt\" id=\"lcnt\">0</span></div>\n"
  "      <div class=\"log-body\" id=\"lb\"></div>\n"
  "    </div>\n"
  "  </div>\n"
  "</div>\n"
  "\n"
  "<div class=\"bottom\">\n"
  "  <div class=\"bc\"><div class=\"bclbl\">Aktivni sektori</div><div class=\"bcv ok\" id=\"bsec\">0/4</div></div>\n"
  "  <div class=\"bc\"><div class=\"bclbl\">LED</div><div class=\"pips\"><div class=\"pip\" id=\"p1\"></div><div class=\"pip\" id=\"p2\"></div><div class=\"pip\" id=\"p3\"></div><div class=\"pip\" id=\"p4\"></div></div></div>\n"
  "  <div class=\"bc\"><div class=\"bclbl\">WiFi RSSI</div><div class=\"bcv\" id=\"brssi\">&#8212;</div></div>\n"
  "  <div class=\"bc\"><div class=\"bclbl\">RAM slobodno</div><div class=\"bcv\" id=\"bram\">&#8212;</div></div>\n"
  "  <div class=\"bc\"><div class=\"bclbl\">Temp MCU</div><div class=\"bcv\" id=\"btemp\">&#8212;</div></div>\n"
  "</div>\n"
  "\n"
  "<script>\n"
  "var ST=Date.now(),lc=0,txc=0,dm=true,dt=0,ci=null,fails=0,online=true;\n"
  "var hs={h1:[],h2:[],h3:[],h4:[]},lbs=[];\n"
  "var lastLoggedTemp=-999;\n"
  "\n"
  "var sc=document.createElement('script');\n"
  "sc.src='https://cdnjs.cloudflare.com/ajax/libs/Chart.js/4.4.1/chart.umd.min.js';\n"
  "sc.onload=function(){\n"
  "  var ctx=document.getElementById('ch').getContext('2d');\n"
  "  ci=new Chart(ctx,{type:'line',data:{labels:lbs,datasets:[\n"
  "    {label:'HC1',data:hs.h1,borderColor:'#f5a535',borderWidth:1.5,pointRadius:0,tension:.3,fill:false,spanGaps:true},\n"
  "    {label:'HC2',data:hs.h2,borderColor:'#60a5fa',borderWidth:1.5,pointRadius:0,tension:.3,fill:false,spanGaps:true},\n"
  "    {label:'HC3',data:hs.h3,borderColor:'#34d399',borderWidth:1.5,pointRadius:0,tension:.3,fill:false,spanGaps:true},\n"
  "    {label:'HC4',data:hs.h4,borderColor:'#9aa5b4',borderWidth:1.5,pointRadius:0,tension:.3,fill:false,spanGaps:true}\n"
  "  ]},options:{\n"
  "    responsive:true,maintainAspectRatio:false,animation:false,\n"
  "    plugins:{legend:{display:false},tooltip:{backgroundColor:'#1c2330',titleColor:'#4a5568',bodyColor:'#e8e4de',bodyFont:{family:'DM Mono',size:11},padding:10,borderColor:'rgba(255,255,255,.07)',borderWidth:1,callbacks:{label:function(c){return ' '+c.dataset.label+': '+(c.parsed.y===null?'--':c.parsed.y.toFixed(1))+' cm'}}}},\n"
  "    scales:{\n"
  "      x:{grid:{color:'rgba(255,255,255,.04)',drawTicks:false},ticks:{color:'#4a5568',font:{family:'DM Mono',size:8},maxTicksLimit:5,maxRotation:0},border:{color:'rgba(255,255,255,.07)'}},\n"
  "      y:{min:0,max:45,grid:{color:'rgba(255,255,255,.04)',drawTicks:false},ticks:{color:'#4a5568',font:{family:'DM Mono',size:8},stepSize:15,callback:function(v){return v+'cm'}},border:{color:'rgba(255,255,255,.07)'}}\n"
  "    }\n"
  "  }});\n"
  "  Chart.register({id:'thr',afterDraw:function(ch){var c=ch.ctx,y=ch.scales.y,yp=y.getPixelForValue(12);c.save();c.setLineDash([3,4]);c.strokeStyle='rgba(248,113,113,.5)';c.lineWidth=1;c.beginPath();c.moveTo(ch.chartArea.left,yp);c.lineTo(ch.chartArea.right,yp);c.stroke();c.restore();}});\n"
  "  ci.update();\n"
  "};\n"
  "document.head.appendChild(sc);\n"
  "\n"
  "function pushChart(h1,h2,h3,h4){\n"
  "  var t=new Date().toTimeString().slice(0,8);\n"
  "  lbs.push(t);hs.h1.push(h1>=999?null:h1);hs.h2.push(h2>=999?null:h2);hs.h3.push(h3>=999?null:h3);hs.h4.push(h4>=999?null:h4);\n"
  "  if(lbs.length>60){lbs.shift();hs.h1.shift();hs.h2.shift();hs.h3.shift();hs.h4.shift();}\n"
  "  if(ci)ci.update('none');\n"
  "}\n"
  "\n"
  "function tick(){\n"
  "  var n=new Date();document.getElementById('clk').textContent=n.toTimeString().slice(0,8);\n"
  "  var u=Math.floor((Date.now()-ST)/1000),h=String(Math.floor(u/3600)).padStart(2,'0'),m=String(Math.floor((u%3600)/60)).padStart(2,'0'),s=String(u%60).padStart(2,'0');\n"
  "  document.getElementById('upt').textContent=h+':'+m+':'+s;\n"
  "}\n"
  "setInterval(tick,1000);\n"
  "\n"
  "function log(msg,type){\n"
  "  lc++;document.getElementById('lcnt').textContent=lc;\n"
  "  var t=new Date().toTimeString().slice(0,8),el=document.createElement('div');\n"
  "  el.className='le';el.innerHTML='<span class=\"lt\">'+t+'</span><span class=\"lm '+type+'\">'+msg+'</span>';\n"
  "  var b=document.getElementById('lb');b.insertBefore(el,b.firstChild);\n"
  "  while(b.children.length>100)b.removeChild(b.lastChild);\n"
  "}\n"
  "\n"
  "function updSensor(id,dist){\n"
  "  var row=document.getElementById('sc'+id),tag=document.getElementById('t'+id),\n"
  "      val=document.getElementById('v'+id),bar=document.getElementById('b'+id),\n"
  "      mk=document.getElementById('sm'+id);\n"
  "  var on=dist>0&&dist<12,pct=dist>=999?0:Math.min(100,Math.round(dist/40*100));\n"
  "  val.textContent=dist>=999?'\\u2014':dist.toFixed(1);\n"
  "  bar.style.width=pct+'%';\n"
  "  if(on){row.classList.add('on');tag.textContent='AKTIVAN';if(mk)mk.classList.add('on');}\n"
  "  else{row.classList.remove('on');tag.textContent=dist>=999?'SLOBODAN':'VAN DOSEGA';if(mk)mk.classList.remove('on');}\n"
  "}\n"
  "\n"
  "function updLampsFromSensors(h1,h2,h3,h4){\n"
  "  var lamps=[false,false,false,false];\n"
  "  if(h1<12){lamps[0]=true;lamps[1]=true;}\n"
  "  if(h2<12){lamps[1]=true;lamps[2]=true;}\n"
  "  if(h3<12){lamps[2]=true;lamps[3]=true;}\n"
  "  if(h4<12){lamps[3]=true;}\n"
  "  lamps.forEach(function(on,i){\n"
  "    var lp=document.getElementById('lp'+(i+1));\n"
  "    if(!lp)return;\n"
  "    if(on){lp.classList.add('on');lp.classList.remove('dim');}\n"
  "    else{lp.classList.remove('on');lp.classList.add('dim');}\n"
  "  });\n"
  "}\n"
  "\n"
  "function updLEDs(arr){\n"
  "  arr.forEach(function(st,i){\n"
  "    var pip=document.getElementById('p'+(i+1));\n"
  "    if(pip){if(st)pip.classList.add('on');else pip.classList.remove('on');}\n"
  "  });\n"
  "  var on=arr.filter(Boolean).length;\n"
  "  document.getElementById('bsec').textContent=on+'/4';\n"
  "  document.getElementById('bsec').className='bcv'+(on>0?' ok':'');\n"
  "}\n"
  "\n"
  "function updUART(mode,ct){\n"
  "  var msg=document.getElementById('umsg'),mod=document.getElementById('umod'),\n"
  "      ctb=document.getElementById('ctbig'),cbd=document.getElementById('cbadges');\n"
  "  mod.textContent=mode;\n"
  "  if(mode==='NORMAL'||mode==='RESET'){\n"
  "    msg.textContent='RESET';msg.className='umsg rst';ctb.textContent='\\u2014';cbd.innerHTML='';\n"
  "  }else{\n"
  "    var m='AUTO:'+ct;\n"
  "    if(msg.textContent!==m){txc++;document.getElementById('utx').textContent=txc;log('TX \\u2192 '+m,'tx');}\n"
  "    msg.textContent=m;msg.className='umsg auto';ctb.textContent=ct;\n"
  "    var names=['HC4','HC3','HC2','HC1'],need=ct<=8?1:ct<=10?2:ct<=12?3:4;\n"
  "    cbd.innerHTML=names.slice(0,need).map(function(n){return '<span class=\"cbadge\">'+n+'</span>';}).join('');\n"
  "  }\n"
  "}\n"
  "\n"
  "/* ── TEMPERATURA UPDATE ──────────────────────────────── */\n"
  "function updTemp(t){\n"
  "  if(t===undefined||t===null)return;\n"
  "  /* -99 = DHT greška, prikaži upozorenje */\n"
  "  if(t<-50){var big=document.getElementById('tempbig');if(big)big.textContent='ERR';var badge=document.getElementById('tempbadge');if(badge){badge.textContent='DHT GREŠKA';badge.className='temp-badge hot';}return;}\n"
  "  var big=document.getElementById('tempbig'),\n"
  "      badge=document.getElementById('tempbadge'),\n"
  "      fill=document.getElementById('tempbar'),\n"
  "      thfill=document.getElementById('thfill'),\n"
  "      thbulb=document.getElementById('thbulb'),\n"
  "      wrap=document.getElementById('tempwrap'),\n"
  "      thermsvg=document.getElementById('thermsvg'),\n"
  "      bttemp=document.getElementById('btemp');\n"
  "  /* Prikaz vrijednosti */\n"
  "  big.textContent=parseFloat(t).toFixed(1);\n"
  "  bttemp.textContent=parseFloat(t).toFixed(1)+'\\u00b0C';\n"
  "  bttemp.className='bcv teal';\n"
  "  /* Procenat 0-50°C skala */\n"
  "  var pct=Math.min(100,Math.max(0,(t/50)*100));\n"
  "  fill.style.height=pct+'%';\n"
  "  /* Termometar SVG fill - tijelo visina 40px od y=2 do y=42 */\n"
  "  /* 0°C = puna duzina (y=2, h=40), 50°C = minimalna (y=42, h=0) */\n"
  "  var fillH=Math.round((pct/100)*38);\n"
  "  var fillY=42-fillH;\n"
  "  thfill.setAttribute('y',fillY);\n"
  "  thfill.setAttribute('height',fillH);\n"
  "  /* Boja prema temperaturi */\n"
  "  var col;\n"
  "  if(t<18){col='#60a5fa';badge.textContent='HLADNO';badge.className='temp-badge';}\n"
  "  else if(t<26){col='#22d3ee';badge.textContent='NORMALNO';badge.className='temp-badge';}\n"
  "  else if(t<34){col='#f5a535';badge.textContent='TOPLO';badge.className='temp-badge warm';}\n"
  "  else{col='#f87171';badge.textContent='VRUĆE';badge.className='temp-badge hot';}\n"
  "  thfill.setAttribute('fill',col);\n"
  "  thbulb.setAttribute('fill',col);\n"
  "  thbulb.style.fill=col;\n"
  "  /* Pozadinski glow za toplo/vruće */\n"
  "  if(t>=26){wrap.classList.add('hot');}else{wrap.classList.remove('hot');}\n"
  "  /* Pulsiranje bulba kada je aktivno */\n"
  "  thermsvg.classList.add('therm-active');\n"
  "  /* Log samo kada se promijeni za >0.5°C */\n"
  "  if(Math.abs(t-lastLoggedTemp)>0.5){\n"
  "    log('DHT \\u2192 '+parseFloat(t).toFixed(1)+'\\u00b0C','temp');\n"
  "    lastLoggedTemp=t;\n"
  "  }\n"
  "}\n"
  "\n"
  "function updStats(d){\n"
  "  if(d.rssi!==undefined)document.getElementById('brssi').textContent=d.rssi+' dBm';\n"
  "  if(d.ram!==undefined)document.getElementById('bram').textContent=Math.round(d.ram/1024)+'KB';\n"
  "  if(d.temp!==undefined&&d.temp!==0){updTemp(d.temp);}\n"
  "}\n"
  "\n"
  "function applyData(d){\n"
  "  var h1=d.hc1||999,h2=d.hc2||999,h3=d.hc3||999,h4=d.hc4||999;\n"
  "  updSensor(1,h1);updSensor(2,h2);updSensor(3,h3);updSensor(4,h4);\n"
  "  document.getElementById('acnt').textContent=[h1,h2,h3,h4].filter(function(x){return x<12;}).length;\n"
  "  pushChart(h1,h2,h3,h4);\n"
  "  updLampsFromSensors(h1,h2,h3,h4);\n"
  "  if(d.led)updLEDs(d.led);\n"
  "  updUART(d.mode||'NORMAL',d.cascadeTime||6);\n"
  "  updStats(d);\n"
  "}\n"
  "\n"
  "function demoTick(){\n"
  "  dt+=0.5;\n"
  "  var d={hc1:999,hc2:999,hc3:999,hc4:999,led:[0,0,0,0],mode:'NORMAL',cascadeTime:6};\n"
  "  var w=Math.sin(dt*.3);\n"
  "  if(w>.2){d.hc4=5+Math.random()*4;d.led[0]=1;d.led[1]=1;d.mode='AUTO';d.cascadeTime=8;}\n"
  "  if(w>.5){d.hc3=6+Math.random()*3;d.led[1]=1;d.led[2]=1;d.cascadeTime=10;}\n"
  "  if(w>.7){d.hc2=7+Math.random()*3;d.led[2]=1;d.led[3]=1;d.cascadeTime=12;}\n"
  "  if(w>.85){d.hc1=8+Math.random()*2;d.led[3]=1;d.cascadeTime=14;}\n"
  "  d.rssi=-55-Math.floor(Math.random()*20);\n"
  "  d.ram=18432+Math.floor(Math.random()*2048);\n"
  "  /* Demo temperatura – sporo oscilira 20–35°C */\n"
  "  d.temp=27+Math.sin(dt*.08)*8+Math.random()*0.5;\n"
  "  applyData(d);\n"
  "}\n"
  "\n"
  "async function poll(){\n"
  "  try{\n"
  "    var r=await fetch('/status',{signal:AbortSignal.timeout(800)});\n"
  "    if(!r.ok)throw new Error();\n"
  "    var d=await r.json();\n"
  "    fails=0;dm=false;\n"
  "    if(!online){online=true;document.getElementById('cdot').classList.remove('off');document.getElementById('ctxt').textContent='ONLINE';document.getElementById('ctxt').style.color='var(--green)';log('Konekcija uspostavljena','ok');}\n"
  "    applyData(d);\n"
  "  }catch(e){\n"
  "    fails++;\n"
  "    if(fails>=3&&online){online=false;document.getElementById('cdot').classList.add('off');document.getElementById('ctxt').textContent='OFFLINE';document.getElementById('ctxt').style.color='var(--red)';log('Konekcija izgubljena','sys');}\n"
  "    if(dm)demoTick();\n"
  "  }\n"
  "}\n"
  "\n"
  "function toggleTheme(){\n"
  "  var b=document.body,btn=document.getElementById('thbtn');\n"
  "  b.classList.toggle('light');\n"
  "  var isL=b.classList.contains('light');\n"
  "  btn.innerHTML=isL?'&#9728; DARK':'&#9788; LIGHT';\n"
  "  try{localStorage.setItem('sils-theme',isL?'light':'dark');}catch(e){}\n"
  "}\n"
  "try{if(localStorage.getItem('sils-theme')==='light'){document.body.classList.add('light');document.getElementById('thbtn').innerHTML='&#9728; DARK';}}catch(e){}\n"
  "\n"
  "setInterval(poll,500);poll();\n"
  "log('SILS monitoring pokrenut','sys');\n"
  "</script>\n"
  "</body>\n"
  "</html>\n"
  "";

WiFiServer server(80);
SoftwareSerial softSerial(A0, A1); // RX=A0, TX=A1

// ── LED pins ───────────────────────────────────────────────
const int led1_Pin = 6;
const int led2_Pin = 9;
const int led3_Pin = 10;
const int led4_Pin = 11;

const int brightnessStart  = 40;
const int brightnessActive = 255;

// ── Ultrasonic pins ────────────────────────────────────────
const int trigPinHC1 = 2,  echoPinHC1 = 3;
const int trigPinHC2 = 4,  echoPinHC2 = 5;
const int trigPinHC3 = 7,  echoPinHC3 = 8;
const int trigPinHC4 = 12, echoPinHC4 = 13;

#define DETECT_DISTANCE   12.0
#define HOLD_TIME         1550
#define ACTIVE_THRESHOLD  1500
#define SEND_INTERVAL     2000

// ── Sector state ───────────────────────────────────────────
bool          sectorActive[4] = {false, false, false, false};
unsigned long sectorTimer[4]  = {0, 0, 0, 0};
bool          manualOn[4]     = {false, false, false, false};

// ── Timers for sensor ────────────────────────────────
unsigned long hc1ActiveSince = 0;
unsigned long hc2ActiveSince = 0;
unsigned long hc3ActiveSince = 0;
unsigned long hc4ActiveSince = 0;

// ── Send state ─────────────────────────────────────────────
int           lastSentTime = 0;
unsigned long lastSentAt   = 0;
bool          signalActive = false;
String        currentMode  = "NORMAL";

// ── Loads ────────────────────────────────────────────────
float HC1distance, HC2distance, HC3distance, HC4distance;
float lastTemp = 0.0;  // UART

// ── Forward declarations ───────────────────────────────────────
void  activateSector(int index);
void  updateSectorTimers();
void  InfoSystem();
float readDistance(int trigPin, int echoPin);
bool  isLongActive(unsigned long since);
int   calcCascadeTime();
void  handleClient(WiFiClient c, String req);
void  serveHTML(WiFiClient c);
void  serveStatus(WiFiClient c);
void  readUARTFromClient();

// ════════════════════════════════════════════════════════════
void setup() {
  pinMode(trigPinHC1, OUTPUT); pinMode(echoPinHC1, INPUT);
  pinMode(trigPinHC2, OUTPUT); pinMode(echoPinHC2, INPUT);
  pinMode(trigPinHC3, OUTPUT); pinMode(echoPinHC3, INPUT);
  pinMode(trigPinHC4, OUTPUT); pinMode(echoPinHC4, INPUT);

  pinMode(led1_Pin, OUTPUT);
  pinMode(led2_Pin, OUTPUT);
  pinMode(led3_Pin, OUTPUT);
  pinMode(led4_Pin, OUTPUT);

  Serial.begin(9600);
  softSerial.begin(9600);
  Serial.println("Server ready.");

  // ── WiFi + static IP ───────────────────────────────────
  IPAddress staticIP(192, 168, 100, 120);
  IPAddress gateway(192, 168, 100, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(8, 8, 8, 8);
  WiFi.config(staticIP, dns, gateway, subnet);

  Serial.print("Spajam se na: "); Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  int att = 0;
  while (WiFi.status() != WL_CONNECTED && att < 40) {
    delay(500); Serial.print("."); att++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi OK!");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
    server.begin();
    Serial.println("Web server started.");
  } else {
    Serial.println("\nWiFi error.");
  }
}

// ════════════════════════════════════════════════════════════
void loop() {
  // ── Web client ──────────────────────────────────────────
  WiFiClient client = server.available();
  if (client) {
    String req = "";
    unsigned long to = millis() + 1000;
    while (client.connected() && millis() < to) {
      if (client.available()) {
        char c = client.read(); req += c;
        if (req.endsWith("\r\n\r\n")) break;
      }
    }
    handleClient(client, req);
    client.stop();
  }

  // ── C# app commands ───────────────────────────────────────────
  InfoSystem();

  // ── Read temp from arduino client ─────────────────
  readUARTFromClient();

  // ── Read sensors data ────────────────────────────────────────
  HC1distance = readDistance(trigPinHC1, echoPinHC1);
  HC2distance = readDistance(trigPinHC2, echoPinHC2);
  HC3distance = readDistance(trigPinHC3, echoPinHC3);
  HC4distance = readDistance(trigPinHC4, echoPinHC4);

  Serial.print("HC1:"); Serial.println(HC1distance, 1);
  Serial.print("HC2:"); Serial.println(HC2distance, 1);
  Serial.print("HC3:"); Serial.println(HC3distance, 1);
  Serial.print("HC4:"); Serial.println(HC4distance, 1);

  // ── Update active timers ───────────────────────────
  if (HC4distance > 0 && HC4distance < DETECT_DISTANCE) {
    if (hc4ActiveSince == 0) hc4ActiveSince = millis();
  } else { hc4ActiveSince = 0; }

  if (HC3distance > 0 && HC3distance < DETECT_DISTANCE && isLongActive(hc4ActiveSince)) {
    if (hc3ActiveSince == 0) hc3ActiveSince = millis();
  } else { hc3ActiveSince = 0; }

  if (HC2distance > 0 && HC2distance < DETECT_DISTANCE && isLongActive(hc4ActiveSince) && isLongActive(hc3ActiveSince)) {
    if (hc2ActiveSince == 0) hc2ActiveSince = millis();
  } else { hc2ActiveSince = 0; }

  if (HC1distance > 0 && HC1distance < DETECT_DISTANCE && isLongActive(hc4ActiveSince) && isLongActive(hc3ActiveSince) && isLongActive(hc2ActiveSince)) {
    if (hc1ActiveSince == 0) hc1ActiveSince = millis();
  } else { hc1ActiveSince = 0; }

  // ── Cascade UART command ─────────────────────────────────
  int cascadeTime = calcCascadeTime();

  if (cascadeTime > 0) {
    bool timeChanged    = (cascadeTime != lastSentTime);
    bool intervalPassed = (millis() - lastSentAt > SEND_INTERVAL);

    if (timeChanged || !signalActive || intervalPassed) {
      String msg = "AUTO:" + String(cascadeTime);
      softSerial.println(msg);
      lastSentTime = cascadeTime;
      lastSentAt   = millis();
      signalActive = true;
      currentMode  = "AUTO";
      Serial.println("UART -> " + msg);
    }
  } else {
    if (signalActive) {
      softSerial.println("RESET");
      signalActive = false;
      lastSentTime = 0;
      currentMode  = "NORMAL";
      Serial.println("UART -> RESET");
    }
  }

  // ── Sector logic for lights ──────────────────
  if (HC1distance > 0 && HC1distance < DETECT_DISTANCE) { activateSector(0); activateSector(1); }
  if (HC2distance > 0 && HC2distance < DETECT_DISTANCE) { activateSector(1); activateSector(2); }
  if (HC3distance > 0 && HC3distance < DETECT_DISTANCE) { activateSector(2); activateSector(3); }
  if (HC4distance > 0 && HC4distance < DETECT_DISTANCE) { activateSector(3); }

  updateSectorTimers();

  int ledPins[4] = {led1_Pin, led2_Pin, led3_Pin, led4_Pin};
  for (int i = 0; i < 4; i++) {
    bool on = sectorActive[i] || manualOn[i];
    analogWrite(ledPins[i], on ? brightnessActive : brightnessStart);
  }

  delay(100);
}

// ── Web request handler ───────────────────────────────────────
void handleClient(WiFiClient c, String req) {
  if (req.indexOf("GET /status") >= 0) serveStatus(c);
  else serveHTML(c);
}

// ── Serve HTML from PROGMEM ───────────────────────────────────
void serveHTML(WiFiClient c) {
  c.println("HTTP/1.1 200 OK");
  c.println("Content-Type: text/html; charset=UTF-8");
  c.println("Connection: close");
  c.println();
  int len = strlen_P(HTML_PAGE);
  char buf[256];
  for (int i = 0; i < len; i += 255) {
    strncpy_P(buf, HTML_PAGE + i, 255);
    buf[255] = '\0';
    c.print(buf);
  }
}

// ── RAM usage ──────────────────────────────────────────────
extern "C" char* sbrk(int incr);
int getFreeRAM() {
  char top;
  return &top - reinterpret_cast<char*>(sbrk(0));
}

// ── /status JSON ─────────────────────────────────────────────
void serveStatus(WiFiClient c) {
  bool led[4];
  for (int i = 0; i < 4; i++) led[i] = sectorActive[i] || manualOn[i];

  String j = "{";
  j += "\"hc1\":" + String(HC1distance, 1) + ",";
  j += "\"hc2\":" + String(HC2distance, 1) + ",";
  j += "\"hc3\":" + String(HC3distance, 1) + ",";
  j += "\"hc4\":" + String(HC4distance, 1) + ",";
  j += "\"led\":[" + String(led[0]?1:0) + "," + String(led[1]?1:0) + "," + String(led[2]?1:0) + "," + String(led[3]?1:0) + "],";
  j += "\"mode\":\"" + currentMode + "\",";
  j += "\"cascadeTime\":" + String(lastSentTime > 0 ? lastSentTime : 6) + ",";
  j += "\"rssi\":" + String(WiFi.RSSI()) + ",";
  j += "\"ram\":" + String(getFreeRAM()) + ",";
  j += "\"temp\":" + String(lastTemp, 1);  // DHT temp from client
  j += "}";

  c.println("HTTP/1.1 200 OK");
  c.println("Content-Type: application/json");
  c.println("Access-Control-Allow-Origin: *");
  c.println("Connection: close");
  c.println();
  c.println(j);
}

// ── Helper functions ──────────────────────────────────────────
bool isLongActive(unsigned long since) {
  return (since > 0 && (millis() - since >= ACTIVE_THRESHOLD));
}

int calcCascadeTime() {
  if (!isLongActive(hc4ActiveSince)) return 0;
  if (isLongActive(hc1ActiveSince))  return 14;
  if (isLongActive(hc2ActiveSince))  return 12;
  if (isLongActive(hc3ActiveSince))  return 10;
  return 8;
}

void activateSector(int index) {
  sectorActive[index] = true;
  sectorTimer[index]  = millis();
}

void updateSectorTimers() {
  for (int i = 0; i < 4; i++) {
    if (!sectorActive[i]) continue;
    bool kept = false;
    if (i == 0 && HC2distance > 0 && HC2distance < DETECT_DISTANCE) kept = true;
    if (i == 1 && HC3distance > 0 && HC3distance < DETECT_DISTANCE) kept = true;
    if (i == 2 && HC4distance > 0 && HC4distance < DETECT_DISTANCE) kept = true;
    if (!kept && (millis() - sectorTimer[i] > HOLD_TIME)) sectorActive[i] = false;
  }
}

void InfoSystem() {
  while (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd.length() >= 6 && cmd.startsWith("LED")) {
      int num   = cmd.charAt(3) - '0';
      int state = cmd.charAt(5) - '0';
      if (num >= 1 && num <= 4) manualOn[num - 1] = (state == 1);
    }
  }
}

// ── Receive TEMP from arduino client via softSerial ──────────────
void readUARTFromClient() {
  while (softSerial.available()) {
    String msg = softSerial.readStringUntil('\n');
    msg.trim();
    if (msg.startsWith("TEMP:")) {
      float t = msg.substring(5).toFloat();
      // -99 = DHT error (sentinel), send next
      // DHT value : -40 do 85°C
      if (t == -99.0 || (t > -40.0 && t < 85.0)) {
        lastTemp = t;
        Serial.print("UART <- "); Serial.println(msg);
      }
    }
  }
}

float readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH, 25000);
  if (duration == 0) return 999.0;
  return (duration * 0.034) / 2.0;
}