//  $Header: /comm/xmlRPC/codeTbl.h 1     09/05/14 3:46 tsupo $
/*! @file
 *  @brief  character code table
 *  @author tsujimura543
 *  @date $Date: 09/05/14 3:46 $
 *  @version $Revision: 1 $
 *  @note
 * History:
 * $Log: /comm/xmlRPC/codeTbl.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     06/02/27 20:57 Tsujimura543
 * rep[] → entity_code_repTbl[] に名前を変更
 * 
 * 1     06/02/27 20:31 Tsujimura543
 * 実体参照→代替文字列変換テーブル関連の定義を encodeURL.c から
 * 分離独立させた。
 */

#ifndef __CODETBL_H__
#define __CODETBL_H__

/* Character Mnemonic Entities 一覧 */
#define CD_QUOT       34 // &quot;     &#34;    "
#define CD_AMP        38 // &amp;      &#38;    &
#define CD_LT         60 // &lt;       &#60;    <
#define CD_GT         62 // &gt;       &#62;    >
#define CD_NBSP      160 // &nbsp;     &#160;   (空白)
#define CD_IEXCL     161 // &iexcl;    &#161;   !
#define CD_CENT      162 // &cent;     &#162;   ￠
#define CD_POUND     163 // &pound;    &#163;   ￡
#define CD_CURREN    164 // &curren;   &#164;   一般通貨記号
#define CD_YEN       165 // &yen;      &#165;   \ 
#define CD_BRVBAR    166 // &brvbar;   &#166;   |
#define CD_SECT      167 // &sect;     &#167;   §
#define CD_UML       168 // &uml;      &#168;   ¨
#define CD_COPY      169 // &copy;     &#169;   (c)
#define CD_ORDF      170 // &ordf;     &#170;   a
#define CD_LAQUO     171 // &laquo;    &#171;   ≪
#define CD_NOT       172 // &not;      &#172;   ￢
#define CD_SHY       173 // &shy;      &#173;   -
#define CD_REG       174 // &reg;      &#174;   (R)
#define CD_MACR      175 // &macr;     &#175;   ￣
#define CD_DEG       176 // &deg;      &#176;   °
#define CD_PLUSMN    177 // &plusmn;   &#177;   ±
#define CD_SUP2      178 // &sup2;     &#178;   2
#define CD_SUP3      179 // &sup3;     &#179;   3
#define CD_ACUTE     180 // &acute;    &#180;   ´
#define CD_MICRO     181 // &micro;    &#181;   μ
#define CD_PARA      182 // &para;     &#182;   ¶
#define CD_MIDDOT    183 // &middot;   &#183;   ・
#define CD_CEDIL     184 // &cedil;    &#184;   ，
#define CD_SUP1      185 // &sup1;     &#185;   1
#define CD_ORDM      186 // &ordm;     &#186;   o
#define CD_RAQUO     187 // &raquo;    &#187;   ≫
#define CD_FRAC14    188 // &frac14;   &#188;   1/4
#define CD_FRAC12    189 // &frac12;   &#189;   1/2
#define CD_FRAC34    190 // &frac34;   &#190;   3/4
#define CD_IQUEST    191 // &iquest;   &#191;   ?
#define CD_AGRAVE    192 // &Agrave;   &#192;   A
#define CD_AACUTE    193 // &Aacute;   &#193;   A
#define CD_ACIRC     194 // &Acirc;    &#194;   A
#define CD_ATILDE    195 // &Atilde;   &#195;   A
#define CD_AUML      196 // &Auml;     &#196;   A
#define CD_ARING     197 // &Aring;    &#197;   Å
#define CD_AELIG     198 // &AElig;    &#198;   A
#define CD_CCEDIL    199 // &Ccedil;   &#199;   C
#define CD_EGRAVE    200 // &Egrave;   &#200;   E
#define CD_EACUTE    201 // &Eacute;   &#201;   E
#define CD_ECIRC     202 // &Ecirc;    &#202;   E
#define CD_EUML      203 // &Euml;     &#203;   Ё
#define CD_IGRAVE    204 // &Igrave;   &#204;   I
#define CD_IACUTE    205 // &Iacute;   &#205;   I
#define CD_ICIRC     206 // &Icirc;    &#206;   I
#define CD_IUML      207 // &Iuml;     &#207;   I
#define CD_ETH       208 // &ETH;      &#208;   D
#define CD_NTILDE    209 // &Ntilde;   &#209;   N
#define CD_OGRAVE    210 // &Ograve;   &#210;   O
#define CD_OACUTE    211 // &Oacute;   &#211;   O
#define CD_OCIRC     212 // &Ocirc;    &#212;   O
#define CD_OTILDE    213 // &Otilde;   &#213;   O
#define CD_OUML      214 // &Ouml;     &#214;   O
#define CD_TIMES     215 // &times;    &#215;   ×
#define CD_OSLASH    216 // &Oslash;   &#216;   O
#define CD_UGRAVE    217 // &Ugrave;   &#217;   U
#define CD_UACUTE    218 // &Uacute;   &#218;   U
#define CD_UCIRC     219 // &Ucirc;    &#219;   U
#define CD_UUML      220 // &Uuml;     &#220;   U
#define CD_YACUTE    221 // &Yacute;   &#221;   Y
#define CD_THORN     222 // &THORN;    &#222;   T
#define CD_SZLIG     223 // &szlig;    &#223;   s (エスツェット)
#define CD_AGRAVEs   224 // &agrave;   &#224;   a
#define CD_AACUTEs   225 // &aacute;   &#225;   a
#define CD_ACIRCs    226 // &acirc;    &#226;   a
#define CD_ATILDEs   227 // &atilde;   &#227;   a
#define CD_AUMLs     228 // &auml;     &#228;   a
#define CD_ARINGs    229 // &aring;    &#229;   a
#define CD_AELIGs    230 // &aelig;    &#230;   a
#define CD_CCEDILs   231 // &ccedil;   &#231;   c
#define CD_EGRAVEs   232 // &egrave;   &#232;   e
#define CD_EACUTEs   233 // &eacute;   &#233;   e
#define CD_ECIRCs    234 // &ecirc;    &#234;   e
#define CD_EUMLs     235 // &euml;     &#235;   ё
#define CD_IGRAVEs   236 // &igrave;   &#236;   i
#define CD_IACUTEs   237 // &iacute;   &#237;   i
#define CD_ICIRCs    238 // &icirc;    &#238;   i
#define CD_IUMLs     239 // &iuml;     &#239;   i
#define CD_ETHs      240 // &eth;      &#240;   d
#define CD_NTILDEs   241 // &ntilde;   &#241;   n
#define CD_OGRAVEs   242 // &ograve;   &#242;   o
#define CD_OACUTEs   243 // &oacute;   &#243;   o
#define CD_OCIRCs    244 // &ocirc;    &#244;   o
#define CD_OTILDEs   245 // &otilde;   &#245;   o
#define CD_OUMLs     246 // &ouml;     &#246;   o
#define CD_DIVIDE    247 // &divide;   &#247;   ÷
#define CD_OSLASHs   248 // &oslash;   &#248;   o
#define CD_UGRAVEs   249 // &ugrave;   &#249;   u
#define CD_UACUTEs   250 // &uacute;   &#250;   u
#define CD_UCIRCs    251 // &ucirc;    &#251;   u
#define CD_UUMLs     252 // &uuml;     &#252;   u
#define CD_YACUTEs   253 // &yacute;   &#253;   y
#define CD_THORNs    254 // &thorn;    &#254;   t
#define CD_YUMLs     255 // &yuml;     &#255;   y
#define CD_OELIG     338 // &OElig;    &#338;   OE
#define CD_OELIGs    339 // &oelig;    &#339;   oe
#define CD_SCARON    352 // &Scaron;   &#352;   S
#define CD_SCARONs   353 // &scaron;   &#353;   s
#define CD_YUML      376 // &Yuml;     &#376;   Y
#define CD_FNOF      402 // &fnof;     &#402;   f
#define CD_CIRC      710 // &circ;     &#710;   ^
#define CD_TILDE     732 // &tilde;    &#732;   ~
#define CD_ALPHA     913 // &Alpha;    &#913;   Α
#define CD_BETA      914 // &Beta;     &#914;   Β
#define CD_GAMMA     915 // &Gamma;    &#915;   Γ
#define CD_DELTA     916 // &Delta;    &#916;   Δ
#define CD_EPSIRON   917 // &Epsilon;  &#917;   Ε
#define CD_ZETA      918 // &Zeta;     &#918;   Ζ
#define CD_ETA       919 // &Eta;      &#919;   Η
#define CD_THETA     920 // &Theta;    &#920;   Θ
#define CD_IOTA      921 // &Iota;     &#921;   Ι
#define CD_KAPPA     922 // &Kappa;    &#922;   Κ
#define CD_LAMBDA    923 // &Lambda;   &#923;   Λ
#define CD_MU        924 // &Mu;       &#924;   Μ
#define CD_NU        925 // &Nu;       &#925;   Ν
#define CD_XI        926 // &Xi;       &#926;   Ξ
#define CD_OMICRON   927 // &Omicron;  &#927;   Ο
#define CD_PI        928 // &Pi;       &#928;   Π
#define CD_RHO       929 // &Rho;      &#929;   Ρ
#define CD_SIGMA     931 // &Sigma;    &#931;   Σ
#define CD_TAU       932 // &Tau;      &#932;   Τ
#define CD_UPSIRON   933 // &Upsilon;  &#933;   Υ
#define CD_PHI       934 // &Phi;      &#934;   Φ
#define CD_CHI       935 // &Chi;      &#935;   Χ
#define CD_PSI       936 // &Psi;      &#936;   Ψ
#define CD_OMEGA     937 // &Omega;    &#937;   Ω
#define CD_ALPHAs    945 // &alpha;    &#945;   α
#define CD_BETAs     946 // &beta;     &#946;   β
#define CD_GAMMAs    947 // &gamma;    &#947;   γ
#define CD_DELTAs    948 // &delta;    &#948;   δ
#define CD_EPSILONs  949 // &epsilon;  &#949;   ε
#define CD_ZETAs     950 // &zeta;     &#950;   ζ
#define CD_ETAs      951 // &eta;      &#951;   η
#define CD_THETAs    952 // &theta;    &#952;   θ
#define CD_IOTAs     953 // &iota;     &#953;   ι
#define CD_KAPPAs    954 // &kappa;    &#954;   κ
#define CD_LAMBDAs   955 // &lambda;   &#955;   λ
#define CD_MUs       956 // &mu;       &#956;   μ
#define CD_NUs       957 // &nu;       &#957;   ν
#define CD_Xis       958 // &xi;       &#958;   ξ
#define CD_OMICRONs  959 // &omicron;  &#959;   ο
#define CD_PIs       960 // &pi;       &#960;   π
#define CD_RHOs      961 // &rho;      &#961;   ρ
#define CD_SIGMAF    962 // &sigmaf;   &#962;   s(ξ の下 2/3、「final sigma」)
#define CD_SIGMAs    963 // &sigma;    &#963;   σ
#define CD_TAUs      964 // &tau;      &#964;   τ
#define CD_UPSILONs  965 // &upsilon;  &#965;   υ
#define CD_PHIs      966 // &phi;      &#966;   φ
#define CD_CHIs      967 // &chi;      &#967;   χ
#define CD_PSIs      968 // &psi;      &#968;   ψ
#define CD_OMEGAs    969 // &omega;    &#969;   ω
#define CD_THETASYM  977 // &thetasym; &#977;   θ
#define CD_UPSIH     978 // &upsih;    &#978;   υ (γ)
#define CD_PIV       982 // &piv;      &#982;   π (ω + ￣)
#define CD_ENSP     8194 // &ensp;     &#8194;  (空白)
#define CD_EMSP     8195 // &emsp;     &#8195;  (空白)
#define CD_THINSP   8201 // &thinsp;   &#8201;  (空白)
#define CD_ZWNJ     8204 // &zwnj;     &#8204;  ?
#define CD_ZWJ      8205 // &zwj;      &#8205;  ?
#define CD_LRM      8206 // &lrm;      &#8206;  ?
#define CD_RLM      8207 // &rlm;      &#8207;  ?
#define CD_NDASH    8211 // &ndash;    &#8211;  ‐
#define CD_MDASH    8212 // &mdash;    &#8212;  ―
#define CD_LSQUO    8216 // &lsquo;    &#8216;  ‘
#define CD_RSQUO    8217 // &rsquo;    &#8217;  ’
#define CD_SBQUO    8218 // &sbquo;    &#8218;  ，
#define CD_LDQUO    8220 // &ldquo;    &#8220;  “
#define CD_RDQUO    8221 // &rdquo;    &#8221;  ”
#define CD_BDQUO    8222 // &bdquo;    &#8222;  〟
#define CD_DAGGERs  8224 // &dagger;   &#8224;  †
#define CD_DAGGER   8225 // &Dagger;   &#8225;  ‡
#define CD_BULL     8226 // &bull;     &#8226;  ・
#define CD_HELLIP   8230 // &hellip;   &#8230;  …
#define CD_PERMIL   8240 // &permil;   &#8240;  ‰
#define CD_PRIMEs   8242 // &prime;    &#8242;  ′
#define CD_PRIME    8243 // &Prime;    &#8243;  ″
#define CD_LSAQUO   8249 // &lsaquo;   &#8249;  〈 
#define CD_RSAQUO   8250 // &rsaquo;   &#8250;  〉
#define CD_OLINE    8254 // &oline;    &#8254;  ￣
#define CD_FRASL    8260 // &frasl;    &#8260;  /
#define CD_EURO     8364 // &euro;     &#8364;  e
#define CD_IMAGE    8465 // &image;    &#8465;  i
#define CD_WEIERP   8472 // &weierp;   &#8472;  P
#define CD_REAL     8476 // &real;     &#8476;  R
#define CD_TRADE    8482 // &trade;    &#8482;  TM
#define CD_ALEFSYM  8501 // &alefsym;  &#8501;  A (アレフ記号[ヘブライ語のA相当の文字])
#define CD_LARR     8592 // &larr;     &#8592;  ←
#define CD_UARR     8593 // &uarr;     &#8593;  ↑
#define CD_RARR     8594 // &rarr;     &#8594;  →
#define CD_DARR     8595 // &darr;     &#8595;  ↓
#define CD_HARR     8596 // &harr;     &#8596;  (← + →、「矢印、左右両方向」)
#define CD_CRARR    8629 // &crarr;    &#8629;  (― + ↓、「キャリッジリターン」)
#define CD_LARRd    8656 // &lArr;     &#8656;  (< + =、「左向き矢印、二重線」)
#define CD_UARRd    8657 // &uArr;     &#8657;  (^ + ||、「上向き矢印、二重線」)
#define CD_RARRd    8658 // &rArr;     &#8658;  ⇒
#define CD_DARRd    8659 // &dArr;     &#8659;  (v + ||、「下向き矢印、二重線」)
#define CD_HARRd    8660 // &hArr;     &#8660;  ⇔
#define CD_FORALL   8704 // &forall;   &#8704;  ∀
#define CD_PART     8706 // &part;     &#8706;  ∂
#define CD_EXIST    8707 // &exist;    &#8707;  ∃
#define CD_EMPTY    8709 // &empty;    &#8709;  (o + /、「空集合」)
#define CD_NABLA    8711 // &nabla;    &#8711;  ∇
#define CD_ISIN     8712 // &isin;     &#8712;  ∈
#define CD_NOTIN    8713 // &notin;    &#8713;  (∈ + /、「含まない」)
#define CD_NI       8715 // &ni;       &#8715;  ∋
#define CD_PROD     8719 // &prod;     &#8719;  П
#define CD_SUM      8721 // &sum;      &#8721;  ∑
#define CD_MINUS    8722 // &minus;    &#8722;  －
#define CD_LOWAST   8727 // &lowast;   &#8727;  *
#define CD_RADIC    8730 // &radic;    &#8730;  √
#define CD_PROP     8733 // &prop;     &#8733;  ∝
#define CD_INFIN    8734 // &infin;    &#8734;  ∞
#define CD_ANG      8736 // &ang;      &#8736;  ∠
#define CD_AND      8743 // &and;      &#8743;  ∧
#define CD_OR       8744 // &or;       &#8744;  ∨
#define CD_CAP      8745 // &cap;      &#8745;  ∩
#define CD_CUP      8746 // &cup;      &#8746;  ∪
#define CD_INT      8747 // &int;      &#8747;  ∫
#define CD_THERE4   8756 // &there4;   &#8756;  ∴
#define CD_SIM      8764 // &sim;      &#8764;  ～
#define CD_CONG     8773 // &cong;     &#8773;  ≒
#define CD_ASYMP    8776 // &asymp;    &#8776;  (= の上下の - を共に ~ に入れ替えたもの、「ほぼ同じ」)
#define CD_NE       8800 // &ne;       &#8800;  ≠
#define CD_EQUIV    8801 // &equiv;    &#8801;  ≡
#define CD_LE       8804 // &le;       &#8804;  ≦
#define CD_GE       8805 // &ge;       &#8805;  ≧
#define CD_SUB      8834 // &sub;      &#8834;  ⊂
#define CD_SUP      8835 // &sup;      &#8835;  ⊃
#define CD_NSUB     8836 // &nsub;     &#8836;  (⊂ + /、「部分集合ではない」)
#define CD_SUBE     8838 // &sube;     &#8838;  ⊆
#define CD_SUPE     8839 // &supe;     &#8839;  ⊇
#define CD_OPLUS    8853 // &oplus;    &#8853;  (+)
#define CD_OTIMES   8855 // &otimes;   &#8855;  (X)
#define CD_PERP     8869 // &perp;     &#8869;  ⊥
#define CD_SDOT     8901 // &sdot;     &#8901;  .
#define CD_LCEIL    8968 // &lceil;    &#8968;  ┌ もしくは 「
#define CD_RCEIL    8969 // &rceil;    &#8969;  ┐
#define CD_LFLOOR   8970 // &lfloor;   &#8970;  └
#define CD_RFLOOR   8971 // &rfloor;   &#8971;  ┘ もしくは 」
#define CD_LANG     9001 // &lang;     &#9001;  〈
#define CD_RANG     9002 // &rang;     &#9002;  〉
#define CD_LOZ      9674 // &loz;      &#9674;  ◇
#define CD_SPADES   9824 // &spades;   &#9824;  スペード
#define CD_CLUBS    9827 // &clubs;    &#9827;  クラブ
#define CD_HEARTS   9829 // &hearts;   &#9829;  ハート
#define CD_DIAMS    9830 // &diams;    &#9830;  ダイア


/* コード変換テーブル */
extern struct replaceTable  {
    char    *src;   /* 実体参照                          */
    char    *dst;   /* Shift_JIS/EUC-JP 出力時の代用表現 */
    int     code;   /* UTF-8 出力時に使用するコード      */
}   entity_code_repTbl[];

#endif  /* __CODETBL_H__ */
