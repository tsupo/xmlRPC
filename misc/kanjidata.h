/*
 *  文字コード判別処理
 *      出典: fj に投稿された記事 (1996年)
 *          Newsgroups: fj.kanji,fj.sources
 *          From: hironobu@tiny.or.jp (Hironobu Takahashi)
 *          Subject: kanji-type (Re: guess kanji code)
 *          Message-ID: <1996Jul2.012859.15825@tiny.or.jp>
 *          Followup-To: fj.kanji
 *          Organization: Tsukuba Internet Club
 *          References: <BABA.96Jun27021124@saori.kusastro.kyoto-u.ac.jp>
 *                      <BABA.96Jun29015026@saori.kusastro.kyoto-u.ac.jp>
 *                      <6338@mozart.castanopsis.iijnet.or.jp>
 *                      <4r7am4$va@post.trc.rwcp.or.jp>
 *          Date: Tue, 2 Jul 1996 01:28:59 GMT
 *
 *      http://katsu.watanabe.name/ancientfj/article.php?mid=%3C1996Jul2%2E012859%2E15825%40tiny%2Eor%2Ejp%3E
 *
 *      参考: kanjidata.[ch] の作者の高橋裕信氏は「漢字→かな(ローマ字)変換
 *            プログラム」kakasi の原作者
 *              http://staff.aist.go.jp/hironobu.takahashi/
 *              http://kakasi.namazu.org/index.html.ja
 *
 * History:
 * $Log: /comm/xmlRPC/misc/kanjidata.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     07/11/13 22:50 Tsujimura543
 * コメントを追加
 * 
 * 3     07/11/13 22:20 Tsujimura543
 * わからなくなってしまっていた「文字コード判別処理」の出典をようやく
 * 突き止めることに成功。出典を明示した
 * 
 * 2     05/12/22 17:47 Tsujimura543
 * ソースコードの書き方を調整
 * 
 * 1     05/12/22 17:44 Tsujimura543
 * changeCode.c で「文字コード判定処理」が必要になったため、以前 fj で見かけた
 * ソースを利用することにする
 */

#ifndef __KANJI_DATA_H__
#define __KANJI_DATA_H__

#ifdef  __CHANGE_CODE_C__
/* euc と ms漢字の特徴を与える各種テーブル */

/* 与えられた 2 byte の文字が EUC であるかどうかを決定するテーブル */

/* もしも JIS ではなくて "JISC6226+NEC98用拡張漢字" ならとあるビットを
   変更すればいいだけ。ここでは「あえて」削ってあります。それは JIS で
   はないことと、多くのユーザーにとっては意味不明のコードポイントでし
   かないからです */

static unsigned long kanji_jiscode_euc[128*8] = {
 0, 0, 0, 0, 0, 0,          0,          0,          /*80*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*81*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*82*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*83*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*84*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*85*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*86*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*87*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*88*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*89*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*8a*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*8b*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*8c*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*8d*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*8e*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*8f*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*90*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*91*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*92*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*93*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*94*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*95*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*96*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*97*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*98*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*99*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*9a*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*9b*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*9c*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*9d*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*9e*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*9f*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*a0*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*a1*/
 0, 0, 0, 0, 0, 0x7ffe003f, 0xc03f800f, 0xffe03fc2, /*a2*/
 0, 0, 0, 0, 0, 0x0000ffc0, 0x7fffffe0, 0x7fffffe0, /*a3*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffff000, /*a4*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffe00, /*a5*/
 0, 0, 0, 0, 0, 0x7fffff80, 0x7fffff80, 0,          /*a6*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xc0007fff, 0xffffc000, /*a7*/
 0, 0, 0, 0, 0, 0x7fffffff, 0x80000000, 0,          /*a8*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*a9*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*aa*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*ab*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*ac*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*ad*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*ae*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*af*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*b0*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*b1*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*b2*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*b3*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*b4*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*b5*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*b6*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*b7*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*b8*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*b9*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*ba*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*bb*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*bc*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*bd*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*be*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*bf*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*c0*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*c1*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*c2*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*c3*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*c4*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*c5*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*c6*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*c7*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*c8*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*c9*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*ca*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*cb*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*cc*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*cd*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*ce*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xfffff000, 0,          /*cf*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*d0*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*d1*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*d2*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*d3*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*d4*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*d5*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*d6*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*d7*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*d8*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*d9*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*da*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*db*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*dc*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*dd*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*de*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*df*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*e0*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*e1*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*e2*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*e3*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*e4*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*e5*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*e6*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*e7*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*e8*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*e9*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*ea*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*eb*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*ec*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*ed*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*ee*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*ef*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*f0*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*f1*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*f2*/
 0, 0, 0, 0, 0, 0x7fffffff, 0xffffffff, 0xfffffffe, /*f3*/
 0, 0, 0, 0, 0, 0x7e000000, 0,          0,          /*f4*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*f5*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*f6*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*f7*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*f8*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*f9*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*fa*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*fb*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*fc*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*fd*/
 0, 0, 0, 0, 0, 0,          0,          0,          /*fe*/
 0, 0, 0, 0, 0, 0,          0,          0           /*ff*/
};

/* 与えられた 2 byte の文字が MS漢字 であるかどうかを決定するテーブル */

/* もしも JIS ではなくて "JISC6226+NEC98用拡張漢字" ならとあるビットを
   変更すればいいだけ。ここでは「あえて」削ってあります。それは JIS で
   はないことと、多くのユーザーにとっては意味不明のコードポイントでし
   かないからです */

static unsigned long kanji_jiscode_mskanji[128*8] = {
 0, 0, 0,          0,          0,          0,          0,          0,          /*80*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xfff800ff, 0x00fe003f, 0xff80ff08, /*81*/
 0, 0, 0x0001ff80, 0xffffffc0, 0x7fffffe1, 0xffffffff, 0xffffffff, 0xffffc000, /*82*/
 0, 0, 0xffffffff, 0xfffffffe, 0xfffffe01, 0xfffffe01, 0xfffffe00, 0,          /*83*/
 0, 0, 0xffffffff, 0x8000fffe, 0xffffc001, 0xfffffffe, 0,          0,          /*84*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*85*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*86*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*87*/
 0, 0, 0,          0,          0x00000001, 0xffffffff, 0xffffffff, 0xfffffff8, /*88*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*89*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*8a*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*8b*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*8c*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*8d*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*8e*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*8f*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*90*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*91*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*92*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*93*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*94*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*95*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*96*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*97*/
 0, 0, 0xffffffff, 0xffffe000, 0x00000001, 0xffffffff, 0xffffffff, 0xfffffff8, /*98*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*99*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*9a*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*9b*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*9c*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*9d*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*9e*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*9f*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*a0*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*a1*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*a2*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*a3*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*a4*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*a5*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*a6*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*a7*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*a8*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*a9*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*aa*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ab*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ac*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ad*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ae*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*af*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*b0*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*b1*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*b2*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*b3*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*b4*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*b5*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*b6*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*b7*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*b8*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*b9*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ba*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*bb*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*bc*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*bd*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*be*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*bf*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*c0*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*c1*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*c2*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*c3*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*c4*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*c5*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*c6*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*c7*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*c8*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*c9*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ca*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*cb*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*cc*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*cd*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ce*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*cf*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*d0*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*d1*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*d2*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*d3*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*d4*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*d5*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*d6*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*d7*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*d8*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*d9*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*da*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*db*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*dc*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*dd*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*de*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*df*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*e0*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*e1*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*e2*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*e3*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*e4*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*e5*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*e6*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*e7*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*e8*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffff8, /*e9*/
 0, 0, 0xffffffff, 0xfffffffe, 0xffffffff, 0xf8000000, 0,          0,          /*ea*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*eb*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ec*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ed*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ee*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*ef*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*f0*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*f1*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*f2*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*f3*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*f4*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*f5*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*f6*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*f7*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*f8*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*f9*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*fa*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*fb*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*fc*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*fd*/
 0, 0, 0,          0,          0,          0,          0,          0,          /*fe*/
 0, 0, 0,          0,          0,          0,          0,          0           /*ff*/
};

/* 0xe0-0xea から始まる EUC と MS漢字 の重なる部分の、漢字の出現頻度表。(EUC)
   1996/6 の fj での使用漢字から作成しました。これらの漢字が EUC で表
   現されていたと仮定した場合の分布です。けっこう局在しています。もし
   もよりよいサンプルがあれば差しかえてくださいね */

static int prob_euc_table[11][92] = {
{0,0,0,4,12,0,0,32,0,183,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,4,0,0,0,0,2,0,0,0,
 12,1,0,0,0,0,1,2,2,0,1,1,15,8,0,2,2,2,0,2,3,4,2,0,0,13,0,3,1,3,0,0,0,0,0,0,
 3,0,11,0,3,0,0,0,0,0,0,0,0,4,0,0,0,0,254,0,3,},
{15,0,0,2,1,0,0,0,0,0,0,0,35,30,0,2,1,0,1,9,1,0,0,0,0,0,0,0,2,0,0,0,17,0,2,
 11,3,76,0,4,0,0,0,1,0,0,0,0,3,0,3,0,0,3,23,3,0,10,21,0,0,0,0,0,1,2,72,32,4,
 3,18,1,12,0,25,61,16,24,0,2,0,13,10,16,3,3,3,0,10,2,6,0,},
{7,0,10,132,6,3,3,3,3,2,0,1,0,0,0,1,0,16,0,0,0,0,1,0,1,7,0,0,0,4,0,0,13,0,68,
 0,0,0,1,0,0,0,47,2,8,1,0,4,0,1,0,8,1,20,2,0,0,0,9,0,0,0,1,0,35,10,0,10,21,0,
 0,0,4,0,0,3,0,7,4,2,1,0,1,0,1,0,0,2,6,0,6,0,},
{11,0,0,2,0,26,0,0,0,9,0,7,41,122,0,0,4,1,1,1,0,9,170,0,1,0,0,0,2,0,0,0,0,0,
 0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,1,1,0,2,0,12,0,0,0,2,2,1,0,16,53,5,0,23,0,
 1,28,11,0,13,23,1,0,133,2,1,1,22,4,1,0,0,4,2,0,0,0,},
{0,0,0,8,0,0,0,0,0,9,0,0,0,63,2,0,0,0,0,0,28,0,3,0,1,1,0,0,0,12,0,2,1,3,0,0,
 0,33,1,0,0,0,0,2,0,0,0,0,1,0,0,0,2,2,0,2,0,0,2,0,0,6,0,0,7,0,0,7,7,0,0,0,38,
 0,0,0,0,11,3,0,6,0,1,1,9,3,0,0,0,0,0,0,},
{15,0,3,2,0,0,0,0,0,0,16,30,4,18,4,14,0,0,2,64,0,0,0,0,0,262,0,0,2,0,0,0,57,
 0,0,0,1,0,0,0,0,0,0,18,0,0,0,0,19,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,17,32,19,
 13,0,8,15,11,0,19,7,0,34,1,0,0,32,4,150,1,3,179,7,10,3,0,0,},
{0,0,0,3,0,13,3,15,0,0,54,0,0,0,0,0,0,0,0,0,0,0,10,0,1,0,0,0,0,0,2,0,0,14,0,
 0,0,135,0,0,0,0,0,7,0,2,0,3,0,0,0,0,0,0,1,1,0,0,49,4,0,0,4,1,4,16,0,0,11,0,
 3,5,2,20,0,1,0,0,37,0,3,0,0,1,7,0,1,1,0,0,4,0,},
{2,0,2,2,28,0,32,1,1,10,0,1,2,0,0,0,2,0,0,0,0,0,5,0,8,2,0,0,12,4,1,4,6,1,0,1,
 0,0,2,0,0,0,0,0,0,0,0,85,0,5,23,0,2,0,0,0,0,1,4,0,0,0,4,0,13,1,0,7,1,2,3,18,
 0,49,0,3,0,0,9,0,0,3,3,0,11,0,12,0,7,2,0,0,},
{0,0,1,3,9,0,60,0,0,0,3,30,0,16,0,0,2,3,0,0,1,0,0,0,0,0,3,1,4,0,0,0,0,0,0,0,0,
 0,0,0,3,0,8,2,0,4,0,3,0,0,0,0,1,0,0,0,0,0,0,0,0,0,70,16,2,1,3,0,19,0,7,0,45,
 6,3,0,8,1,5,4,9,0,0,0,6,0,0,0,0,0,0,0,},
{9,0,0,9,9,0,0,1,0,0,1,30,14,47,30,0,0,7,0,0,0,8,0,0,0,61,0,0,2,10,0,0,0,0,0,
 0,2,0,0,0,0,3,1,0,2,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,0,0,0,40,35,6,5,8,3,20,1,
 0,2,5,2,9,77,10,11,0,5,79,15,7,0,3,22,0,2,2,0,},
{0,0,0,26,5,0,0,0,0,0,0,0,19,7,0,0,0,0,3,0,2,0,1,0,1,3,0,0,0,0,1,0,1,0,0,0,3,
 1,0,0,0,1,0,14,0,0,0,1,0,0,3,0,0,0,3,0,0,0,0,1,0,0,0,9,3,0,8,0,0,0,1,0,10,3,
 0,0,10,0,4,157,0,1,2,7,0,0,1,14,0,0,0,0,}};

/* 0xe0-0xea から始まる MS漢字 の出現頻度表。
   1996/6 の fj での使用漢字から作成しました。これらの漢字が MS漢字 で
   表現されていたと仮定した場合の分布です。*/

static int prob_mskanji_table[11][92]={
{0,4,12,0,0,32,0,183,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,4,0,0,0,0,2,0,0,0,12,1,0,
 0,0,0,1,2,2,0,1,1,15,8,0,2,2,2,0,2,3,4,2,0,0,13,0,3,1,3,0,0,0,0,0,0,3,0,11,0,
 3,0,0,0,0,0,0,0,0,4,0,0,0,0,254,0,3,0,0,},
{10,132,6,3,3,3,3,2,0,1,0,0,0,1,0,16,0,0,0,0,1,0,1,7,0,0,0,4,0,0,13,0,68,0,0,
 0,1,0,0,0,47,2,8,1,0,4,0,1,0,8,1,20,2,0,0,0,9,0,0,0,1,0,35,10,0,10,21,0,0,0,
 4,0,0,3,0,7,4,2,1,0,1,0,1,0,0,2,6,0,6,0,0,0,},
{0,8,0,0,0,0,0,9,0,0,0,63,2,0,0,0,0,0,28,0,3,0,1,1,0,0,0,12,0,2,1,3,0,0,0,33,
 1,0,0,0,0,2,0,0,0,0,1,0,0,0,2,2,0,2,0,0,2,0,0,6,0,0,7,0,0,7,7,0,0,0,38,0,0,0,
 0,11,3,0,6,0,1,1,9,3,0,0,0,0,0,0,4,5,},
{0,3,0,13,3,15,0,0,54,0,0,0,0,0,0,0,0,0,0,0,10,0,1,0,0,0,0,0,2,0,0,14,0,0,0,
 135,0,0,0,0,0,7,0,2,0,3,0,0,0,0,0,0,1,1,0,0,49,4,0,0,4,1,4,16,0,0,11,0,3,5,
 2,20,0,1,0,0,37,0,3,0,0,1,7,0,1,1,0,0,4,0,0,0,},
{1,3,9,0,60,0,0,0,3,30,0,16,0,0,2,3,0,0,1,0,0,0,0,0,3,1,4,0,0,0,0,0,0,0,0,0,
 0,0,3,0,8,2,0,4,0,3,0,0,0,0,1,0,0,0,0,0,0,0,0,0,70,16,2,1,3,0,19,0,7,0,45,6,
 3,0,8,1,5,4,9,0,0,0,6,0,0,0,0,0,0,0,0,0,},
{0,26,5,0,0,0,0,0,0,0,19,7,0,0,0,0,3,0,2,0,1,0,1,3,0,0,0,0,1,0,1,0,0,0,3,1,0,
 0,0,1,0,14,0,0,0,1,0,0,3,0,0,0,3,0,0,0,0,1,0,0,0,9,3,0,8,0,0,0,1,0,10,3,0,0,
 10,0,4,157,0,1,2,7,0,0,1,14,0,0,0,0,0,0,},
{6,14,1,15,0,0,0,20,0,0,1,16,0,1,1,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,2,
 0,1,2,4,0,2,0,16,0,12,0,0,9,65,3,0,1,0,0,0,0,0,5,0,0,0,7,0,0,7,35,1,0,0,7,0,
 4,7,1,10,0,13,0,0,1,6,0,3,0,3,0,24,19,3,0,13,},
{2,0,1,0,0,0,1,2,0,2,0,15,1,1,24,11,3,103,40,3,0,0,0,3,0,0,0,0,0,0,1,0,0,0,0,
 0,0,0,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,28,1,1,11,329,24,5,0,
 14,2,14,7,1,7,52,0,0,1,35,21,2,0,15,0,17,0,0,9,0,0,},
{0,1,0,9,2,12,0,6,4,2,0,9,0,1,1,0,0,0,3,0,0,16,1,0,0,2,1,29,0,0,0,0,9,0,0,0,6,
 10,0,2,0,2,6,0,0,3,11,0,0,0,2,0,0,0,0,0,0,0,7,0,0,0,17,0,11,3,12,1,4,4,7,4,0,
 2,0,6,18,3,0,0,15,0,13,1,6,4,2,0,0,0,11,25,},
{1,3,0,0,0,0,2,1,0,0,4,44,0,0,0,1,1,25,1,0,1,0,0,0,0,0,1,0,94,1,0,0,0,2,0,0,0,
 0,0,0,0,2,8,0,26,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,23,0,12,4,26,0,0,0,29,0,0,
 0,1,10,24,1,0,2,33,2,2,11,0,0,16,0,0,0,0,0,},
{9,2,0,0,0,0,1,0,0,0,23,58,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,37,0,8,11,34,0,0,6,10,0,5,
 0,10,14,31,0,0,2,15,13,0,0,1,0,12,0,0,0,0,0,}};
#endif  /* __CHANGE_CODE_C__ */

/* 文字コード */
enum KANJI_CODE {
    KC_UNKNOWN,     /* 不明                                          */
    KC_BROKEN,      /* JISでもEUC-JPでもMS漢字でもない何か別のコード */
    KC_JISC6226_78, /* JIS 1978 (旧JIS)                              */
    KC_JISX0208_83, /* JIS 1983 (新JIS)                              */
    KC_JISX0208_90, /* JIS 1990                                      */
    KC_EUC,         /* EUC-JP                                        */
    KC_MSKANJI      /* MS漢字(CP932)                                 */
};

/*
 *  課題: 完全に CP932 対応にするには「NEC98用拡張漢字」を無視すること
 *        はできない (IBM PC で追加された漢字も同様)
 */

#endif  /* __KANJI_DATA_H__ */
