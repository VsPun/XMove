

#if INPUT_CONTROL_EN==1

struct t9PY_index
{
	const unsigned long  t9PY;
	const unsigned char *PY;
	const unsigned char *PY_mb;
};

struct t9py_struct
{
	unsigned char  pysrf;       //���뷨ѡ��
	unsigned char  firstno;     //����ĵ�һ�����ְ���
	unsigned char  mblen;       //������ĳ���
	unsigned char  mbtimes;     //����л��Ĵ���
	unsigned long t9py;		//���ְ������,��ϳ�16���ƣ����簴��246��Ϊ0x246
	const struct t9PY_index  *t9PY_addr;
};


const unsigned char t9PY_indexlen[10] = {1,1,55,33,38,57,44,79,19,74};   //��ÿ�����ּ���ʼ��ƴ�������������

/*******************************************************************************
**���ܣ�ƴ�����뷨�������б�
**������magicchip
**���ڣ�20080509
*******************************************************************************/
const unsigned char PY_mb_space []={""};
const unsigned char PY_mb_a     []={"������߹�����"};
const unsigned char PY_mb_ai    []={"���������������������������������������������"};
const unsigned char PY_mb_an    []={"���������������������������������������"};
const unsigned char PY_mb_ang   []={"��������"};
const unsigned char PY_mb_ao    []={"�������°��ð��������������������������������"};
const unsigned char PY_mb_ba    []={"�Ѱ˰ɰְΰհϰͰŰǰӰ԰Ȱаʰ̰Ұ������������"};
const unsigned char PY_mb_bai   []={"�ٰװڰܰذݰ۲���������"};
const unsigned char PY_mb_ban   []={"��������߰����������������"};
const unsigned char PY_mb_bang  []={"���������������������"};
const unsigned char PY_mb_bao   []={"�����������������������ٱ����������������������������"};
const unsigned char PY_mb_bei   []={"�������������������������������������������"};
const unsigned char PY_mb_ben   []={"�����������������"};
const unsigned char PY_mb_beng  []={"�ı��±��Ű������"};
const unsigned char PY_mb_bi    []={"�ȱʱձǱ̱رܱƱϱ۱˱ɱڱͱұױٱαбӱֱݱѱ�������޵ݩ����ذ���������������������������������������������"};
const unsigned char PY_mb_bian  []={"�߱�������ޱ���������������������������"};
const unsigned char PY_mb_biao  []={"���������������������"};
const unsigned char PY_mb_bie   []={"�������"};
const unsigned char PY_mb_bin   []={"������������������������������"};
const unsigned char PY_mb_bing  []={"����������������������������"};
const unsigned char PY_mb_bo    []={"����������������������������������ز����������ǲ�������������ެ�������"};
const unsigned char PY_mb_bu    []={"�������������������������������������߲"};
const unsigned char PY_mb_ca    []={"��������"};
const unsigned char PY_mb_cai   []={"�²ŲĲƲòɲʲǲȲ˲�"};
const unsigned char PY_mb_can   []={"�ϲв��βҲѲͲ����������"};
const unsigned char PY_mb_cang  []={"�زֲײղ���"};
const unsigned char PY_mb_cao   []={"�ݲٲܲ۲��������"};
const unsigned char PY_mb_ce    []={"���߲����"};
const unsigned char PY_mb_cen   []={"����"};
const unsigned char PY_mb_ceng  []={"�������"};
const unsigned char PY_mb_cha   []={"�����������ɲ��������������������"};
const unsigned char PY_mb_chai  []={"�˲���������٭"};
const unsigned char PY_mb_chan  []={"��������������������������������������������������"};
const unsigned char PY_mb_chang []={"���������������������������������������������������"};
const unsigned char PY_mb_chao  []={"�����������������˴³���������"};
const unsigned char PY_mb_che   []={"�����������߳����"};
const unsigned char PY_mb_chen  []={"�óƳ����������³ĳȳ��������������������"};
const unsigned char PY_mb_cheng []={"�ɳ�ʢ�ųƳǳ̳ʳϳͳѳҳγȳ�����������������������ة�"};
const unsigned char PY_mb_chi   []={"�Գ߳ٳس�ճ�ݳֳܳ�޳ڳ۳��������ܯ����������������������߳������"};
const unsigned char PY_mb_chong []={"���س����ӿ������������"};
const unsigned char PY_mb_chou  []={"���������������ٱ�����"};
const unsigned char PY_mb_chu   []={"�������������������������������������ۻ���ء����������"};
const unsigned char PY_mb_chuai []={"�����������"};
const unsigned char PY_mb_chuan []={"������������������������"};
const unsigned char PY_mb_chuang[]={"��������������"};
const unsigned char PY_mb_chui  []={"����������׵����"};
const unsigned char PY_mb_chun  []={"����������������ݻ��"};
const unsigned char PY_mb_chuo  []={"����������"};
const unsigned char PY_mb_ci    []={"�δ˴ʴɴȴƴŴǴ̴��ŴôͲ�����������"};
const unsigned char PY_mb_cong  []={"�ӴԴдҴϴ������������"};
const unsigned char PY_mb_cou   []={"������"};
const unsigned char PY_mb_cu    []={"�ִ״ش����������������"};
const unsigned char PY_mb_cuan  []={"�ܴڴ���ߥ������"};
const unsigned char PY_mb_cui   []={"�ߴ�ݴ�޴�˥������������"};
const unsigned char PY_mb_cun   []={"���������"};
const unsigned char PY_mb_cuo   []={"������������������������"};
const unsigned char PY_mb_da    []={"����������������������������"};
const unsigned char PY_mb_dai   []={"�������������������������߾�����߰�����ܤ"};
const unsigned char PY_mb_dan   []={"������������������������������ʯ��������������������"};
const unsigned char PY_mb_dang  []={"����������������������"};
const unsigned char PY_mb_dao   []={"���������������������������������߶"};
const unsigned char PY_mb_de    []={"�ĵصõµ��"};
const unsigned char PY_mb_deng  []={"�ȵƵ˵ǳεɵʵ������������"};
const unsigned char PY_mb_di    []={"�صڵ׵͵еֵε۵ݵյܵ޵̵ĵ���ѵϵҵԵ���ۡ��ڮ��������ص����ݶ����������"};
const unsigned char PY_mb_dia	[]={"��"};
const unsigned char PY_mb_dian  []={"�������ߵ�������������������������"};
const unsigned char PY_mb_diao  []={"�����������������������"};
const unsigned char PY_mb_die   []={"���������������ܦ������������"};
const unsigned char PY_mb_ding  []={"������������������������������������"};
const unsigned char PY_mb_diu   []={"����"};
const unsigned char PY_mb_dong  []={"����������������������������������"};
const unsigned char PY_mb_dou   []={"������������������������"};
const unsigned char PY_mb_du    []={"���ȶ��ɶ¶��ǶƶĶöŶ������ʶ��������������ܶ"};
const unsigned char PY_mb_duan  []={"�ζ̶϶˶Ͷ������"};
const unsigned char PY_mb_dui   []={"�ԶӶѶҶ�������"};
const unsigned char PY_mb_dun   []={"�ֶٶ׶նض۶ܶڶݲ��������������"};
const unsigned char PY_mb_duo   []={"����������޶��Զȶ��������������"};
const unsigned char PY_mb_e     []={"��Ŷ������ﰢ������������������������ݭ��������ج����"};
const unsigned char PY_mb_en    []={"������"};
const unsigned char PY_mb_er    []={"���������������������٦����"};
const unsigned char PY_mb_fa    []={"��������������������"};
const unsigned char PY_mb_fan   []={"���������������������������������������ެ�����"};
const unsigned char PY_mb_fang  []={"�ŷ����ķ����÷·�����������������"};
const unsigned char PY_mb_fei   []={"�ǷɷʷѷηϷ˷ͷзƷ̷�������������������������������"};
const unsigned char PY_mb_fen   []={"�ַݷҷ۷طܷ߷׷޷�ӷٷԷշ������������"};
const unsigned char PY_mb_feng  []={"�����������������ٺۺ������"};
const unsigned char PY_mb_fo    []={"��"};
const unsigned char PY_mb_fou   []={"���"};
const unsigned char PY_mb_fu    []={"�����������������������������������򸸷����󸳸���������������������������������и����������������������������������������������������������ݳ���������߻ۮܽ��"};
const unsigned char PY_mb_ga    []={"����и¿�����٤���������"};
const unsigned char PY_mb_gai   []={"�øĸǸŸƽ�����ؤ����"};
const unsigned char PY_mb_gan   []={"�ϸɸиҸ͸ʸθ̸˸Ӹ�����������ߦ�����������"};
const unsigned char PY_mb_gang  []={"�ոָٸ۸׸ڸܸԸؿ�����"};
const unsigned char PY_mb_gao   []={"�߸����ݸ����۬ھ���غ�����޻"};
const unsigned char PY_mb_ge    []={"�������������￩���������ٺϸ��������ܪ���������ت���������"};
const unsigned char PY_mb_gei   []={"��"};
const unsigned char PY_mb_gen   []={"������ݢب��"};
const unsigned char PY_mb_geng  []={"�����������������������"};
const unsigned char PY_mb_gong  []={"���������������������������������������"};
const unsigned char PY_mb_gou   []={"��������������������������������ڸ��������"};
const unsigned char PY_mb_gu    []={"�ŹɹĹȹʹ¹��ù˹̹͹����ǹ����Ƽֹ��������������������������ڬ�����������������"};
const unsigned char PY_mb_gua   []={"�ҹιϹѹй����������ڴ"};
const unsigned char PY_mb_guai  []={"�ֹչ���"};
const unsigned char PY_mb_guan  []={"�عܹٹ۹ݹ߹޹�ڹ��������ݸ����������"};
const unsigned char PY_mb_guang []={"������������"};
const unsigned char PY_mb_gui   []={"��������������������Ȳ���������������������"};
const unsigned char PY_mb_gun   []={"�������������"};
const unsigned char PY_mb_guo   []={"�����������������������������������"};
const unsigned char PY_mb_ha    []={"����Ϻ��"};
const unsigned char PY_mb_hai   []={"�������Ⱥ���������������"};
const unsigned char PY_mb_han   []={"����������������������������������������������������������"};
const unsigned char PY_mb_hang  []={"���ﺽ�������������"};
const unsigned char PY_mb_hao   []={"�úźƺ����º����ĺѸ�������������޶"};
const unsigned char PY_mb_he    []={"�ͺȺϺӺ̺˺κǺɺغպֺк׺ʺѺҺ����������������ڭ����"};
const unsigned char PY_mb_hei   []={"�ں�"};
const unsigned char PY_mb_hen   []={"�ܺݺ޺�"};
const unsigned char PY_mb_heng  []={"���ߺ��������޿"};
const unsigned char PY_mb_hong  []={"����������ڧ��ޮ��ް��ݦ��"};
const unsigned char PY_mb_hou   []={"������������ܩ����������"};
const unsigned char PY_mb_hu    []={"��������������������������������Ϸ�˺ͺ�������������������������������������������������"};
const unsigned char PY_mb_hua   []={"���������������������������"};
const unsigned char PY_mb_huai  []={"��������������"};
const unsigned char PY_mb_huan  []={"���������������û»������������ߧ����ۨ���ۼ����������"};
const unsigned char PY_mb_huang []={"�ƻŻλĻɻ˻ʻѻ̻Ȼǻлͻ�������������"};
const unsigned char PY_mb_hui   []={"�ػ�һ�ӻ�Իٻڻݻ޻ջֻ�ۻ߻׻仲�ܻ�������ޥ����������ڶ�����������"};
const unsigned char PY_mb_hun   []={"���������������ڻ"};
const unsigned char PY_mb_huo   []={"�������ͻ���������������޽߫������"};
const unsigned char PY_mb_ji    []={"�������ȼ��������Ǽ����Ƽ������ļ�ϵ���������ʻ������������������������������������������������¼ü����������˼̸���������������������ڵ��������ߴ����������������������آ��ܸ٥�������ު����"};
const unsigned char PY_mb_jia   []={"�ҼӼټۼܼ׼Ѽмμݼ޼ϼԼռؼ��Ѽ�������������������٤��������ۣ����"};
const unsigned char PY_mb_jian  []={"��������������潨��������߼��齡�������������ǳ���������𽢼���뽤��������������������������������������������������"};
const unsigned char PY_mb_jiang []={"������������������������ǿ��������������������"};
const unsigned char PY_mb_jiao  []={"�нŽ��ǽ̽Ͻɾ���������У�����ƽ��ý������νѽ����Ƚ½ͽĽ���ܴ������������������ٮ������"};
const unsigned char PY_mb_jie   []={"�ӽڽֽ�Խؽ�����ҽ��׽ٽ�߽���ۿ��ս۽ܽݽ�޼��������������������ڦ����ڵ"};
const unsigned char PY_mb_jin   []={"�����������ﾡ�������������������������������ݣ�������������"};
const unsigned char PY_mb_jing  []={"�������������������������������������������������������������������ݼ���������"};
const unsigned char PY_mb_jiong []={"��������"};
const unsigned char PY_mb_jiu   []={"�;žƾɾþ��Ⱦ��˾��¾Ǿʾ��ľ̾�������������������"};
const unsigned char PY_mb_ju    []={"��پ޾־߾���Ӿ۾оվؾھܾ�ϾѾ��Ҿݹ�۾㳵�׾Ҿ��������������������������������������������ڪ��"};
const unsigned char PY_mb_juan  []={"��Ȧ�������۲�������������"};
const unsigned char PY_mb_jue   []={"�������Ǿ����������������������������������ާ����������"};
const unsigned char PY_mb_jun   []={"�������������꿢����������������"};
const unsigned char PY_mb_ka    []={"��������������"};
const unsigned char PY_mb_kai   []={"�������������������������"};
const unsigned char PY_mb_kan   []={"��������Ƕ���������٩�ݨ��"};
const unsigned char PY_mb_kang  []={"��������������������"};
const unsigned char PY_mb_kao   []={"����������������"};
const unsigned char PY_mb_ke    []={"�ȿɿ˿ÿƿſ̿οͿǿʿ��¿Ŀ��������������������������������"};
const unsigned char PY_mb_ken   []={"�Ͽпҿ���"};
const unsigned char PY_mb_keng  []={"�ӿ��"};
const unsigned char PY_mb_kong  []={"�տ׿ؿ�������"};
const unsigned char PY_mb_kou   []={"�ڿۿٿ�ޢ������ߵ"};
const unsigned char PY_mb_ku    []={"�޿��ݿ�߿������ܥ�"};
const unsigned char PY_mb_kua   []={"������٨"};
const unsigned char PY_mb_kuai  []={"�����������ۦ����"};
const unsigned char PY_mb_kuan  []={"�����"};
const unsigned char PY_mb_kuang []={"�����������ڿ������ڲ������"};
const unsigned char PY_mb_kui   []={"�������������������������������������������ظ������"};
const unsigned char PY_mb_kun   []={"��������������������"};
const unsigned char PY_mb_kuo   []={"��������������"};
const unsigned char PY_mb_la    []={"���������������������������"};
const unsigned char PY_mb_lai   []={"���������������������"};
const unsigned char PY_mb_lan   []={"����������������������������������������"};
const unsigned char PY_mb_lang  []={"������������������ݹ������"};
const unsigned char PY_mb_lao   []={"���������������������������������������"};
const unsigned char PY_mb_le    []={"����������߷����"};
const unsigned char PY_mb_lei   []={"��������������������������ڳ������������"};
const unsigned char PY_mb_leng  []={"������ܨ�"};
const unsigned char PY_mb_li    []={"��������������������������������������������������������������������ٳٵ۪����ݰ���������������������ت߿������������޼���������������������������"};
const unsigned char PY_mb_lia	[]={"��"};
const unsigned char PY_mb_lian  []={"������������������������������������������������"};
const unsigned char PY_mb_liang []={"������������������������ܮ�������ݹ"};
const unsigned char PY_mb_liao  []={"����������������������������ޤ����������"};
const unsigned char PY_mb_lie   []={"�������������������������"};
const unsigned char PY_mb_lin   []={"�����������������������������������������������"};
const unsigned char PY_mb_ling  []={"��������������������������������������۹��������������"};
const unsigned char PY_mb_liu   []={"����������������������µ½����������������"};
const unsigned char PY_mb_long  []={"��£����¡¢Ū����¤���������������"};
const unsigned char PY_mb_lou   []={"¥§©ª¶¦¨�����������������"};
const unsigned char PY_mb_lu    []={"·¶¼¹½¯¬³±«­®µ°��²¸¾º»´��������ޤ�������������������"};
const unsigned char PY_mb_luan  []={"��������������������"};
const unsigned char PY_mb_lue   []={"�����"};
const unsigned char PY_mb_lun   []={"����������������"};
const unsigned char PY_mb_luo   []={"�������������������������翩���������������������������"};
const unsigned char PY_mb_lv    []={"������¿���������������������������������"};
const unsigned char PY_mb_ma    []={"������������Ĩ������Ħ��������"};
const unsigned char PY_mb_mai   []={"������������۽��ݤ"};
const unsigned char PY_mb_man   []={"������������������á���ܬ�����������"};
const unsigned char PY_mb_mang  []={"æâäçãå��������"};
const unsigned char PY_mb_mao   []={"ëðñèìîòïóíêé���������������������"};
const unsigned char PY_mb_me    []={"ô��"};
const unsigned char PY_mb_mei   []={"ûÿúþ��ø��öùõü÷����ý������ĭ����������ݮ�����"};
const unsigned char PY_mb_men   []={"�������������"};
const unsigned char PY_mb_meng  []={"����������������å������������������ޫ"};
const unsigned char PY_mb_mi    []={"��������������������������������������������������������"};
const unsigned char PY_mb_mian  []={"������������������������������"};
const unsigned char PY_mb_miao  []={"������������������������������"};
const unsigned char PY_mb_mie   []={"���������ؿ"};
const unsigned char PY_mb_min   []={"������������������������������"};
const unsigned char PY_mb_ming  []={"��������������ڤ���������"};
const unsigned char PY_mb_miu   []={"����"};
const unsigned char PY_mb_mo    []={"��ĥĨĩĤīûĪĬħģĦġĮİ��ĭ����ðį�������Ժ���Ģ�����������������"};
const unsigned char PY_mb_mou   []={"ĳıĲ������ٰ����"};
const unsigned char PY_mb_mu    []={"ľĸĶĻĿĹ��Ĳģ��ĺĵĴļĽ��ķ�������������"};
const unsigned char PY_mb_na    []={"������������������������"};
const unsigned char PY_mb_nai   []={"��������������ܵ��ؾ٦"};
const unsigned char PY_mb_nan   []={"����������������"};
const unsigned char PY_mb_nang  []={"��������߭"};
const unsigned char PY_mb_nao   []={"����������ث������������"};
const unsigned char PY_mb_ne    []={"��������ګ"};
const unsigned char PY_mb_nei   []={"��������"};
const unsigned char PY_mb_nen   []={"���"};
const unsigned char PY_mb_neng  []={"��"};
const unsigned char PY_mb_ni    []={"���������������������������������٣�������"};
const unsigned char PY_mb_nian  []={"��������������ճإ���������"};
const unsigned char PY_mb_niang []={"����"};
const unsigned char PY_mb_niao  []={"������������"};
const unsigned char PY_mb_nie   []={"������������������������ؿ"};
const unsigned char PY_mb_nin   []={"���"};
const unsigned char PY_mb_ning  []={"š��������Ţ�������"};
const unsigned char PY_mb_niu   []={"ţŤŦť�������"};
const unsigned char PY_mb_nong  []={"ŪŨũŧ��ٯ"};
const unsigned char PY_mb_nu    []={"ŭŬū��������"};
const unsigned char PY_mb_nuan  []={"ů"};
const unsigned char PY_mb_nue   []={"Űű��"};
const unsigned char PY_mb_nuo   []={"ŲŵųŴ���������"};
const unsigned char PY_mb_nv    []={"Ů�����"};
const unsigned char PY_mb_o     []={"Ŷ���"};
const unsigned char PY_mb_ou    []={"żŻŷźŸ��ŽŹ���ک��"};
const unsigned char PY_mb_pa    []={"����ſž�Ұ�������������"};
const unsigned char PY_mb_pai   []={"����������������ٽ��"};
const unsigned char PY_mb_pan   []={"���������������ͷ������������������"};
const unsigned char PY_mb_pang  []={"���������Ұ���������"};
const unsigned char PY_mb_pao   []={"������������������������"};
const unsigned char PY_mb_pei   []={"�����������������������������"};
const unsigned char PY_mb_pen   []={"������"};
const unsigned char PY_mb_peng  []={"������������������������������ܡ���"};
const unsigned char PY_mb_pi    []={"��Ƥ��ƥ������ƨƢƧƣƦ������ơƩ������ا�������ߨۯ������ܱ�����������������������"};
const unsigned char PY_mb_pian  []={"Ƭƪƭƫ�����������������"};
const unsigned char PY_mb_piao  []={"ƱƮƯư���ݳ�������������"};
const unsigned char PY_mb_pie   []={"ƳƲ���"};
const unsigned char PY_mb_pin   []={"ƷƶƸƴƵ�������"};
const unsigned char PY_mb_ping  []={"ƽƾƿ����ƹƼƻƺ�������ٷ"};
const unsigned char PY_mb_po    []={"�����������Ȳ����ӷ����������۶�������"};
const unsigned char PY_mb_pou   []={"������"};
const unsigned char PY_mb_pu    []={"�����׸����������������������ֱ��ձ����������������W"};
const unsigned char PY_mb_qi    []={"�������������������������������������������������������������������������������������ݽޭ���������ܻ��ؽ��ٹ��������������������������������"};
const unsigned char PY_mb_qia   []={"ǡ����Ǣ������"};
const unsigned char PY_mb_qian  []={"ǰǮǧǣǳǩǷǦǶǥǨǯǬǴǫǱǸ��ǤǲǭǵǪ���������ٻ������ݡ����ܷ�����������"};
const unsigned char PY_mb_qiang []={"ǿǹǽ��ǻǺǼǾ������������������������"};
const unsigned char PY_mb_qiao  []={"�����������¿�����������ȸ������������������������ڽ��"};
const unsigned char PY_mb_qie   []={"������������ۧ���������٤��"};
const unsigned char PY_mb_qin   []={"����������������������������������������������"};
const unsigned char PY_mb_qing  []={"��������������������������������������������������"};
const unsigned char PY_mb_qiong []={"�����������������"};
const unsigned char PY_mb_qiu   []={"���������������������������������ٴ�������������"};
const unsigned char PY_mb_qu    []={"ȥȡ��Ȣ������Ȥ��������ȣ���޾��ޡ��۾ڰ�����������������������"};
const unsigned char PY_mb_quan  []={"ȫȨȰȦȭȮȪȯȧȬȩ�����ڹ����������"};
const unsigned char PY_mb_que   []={"ȴȱȷȸȳȵȲȶ�����"};
const unsigned char PY_mb_qun   []={"Ⱥȹ����"};
const unsigned char PY_mb_ran   []={"ȾȼȻȽ������"};
const unsigned char PY_mb_rang  []={"����ȿ�������"};
const unsigned char PY_mb_rao   []={"�����������"};
const unsigned char PY_mb_re    []={"��������"};
const unsigned char PY_mb_ren   []={"���������������������������������"};
const unsigned char PY_mb_reng  []={"����"};
const unsigned char PY_mb_ri    []={"��"};
const unsigned char PY_mb_rong  []={"������������������������������"};
const unsigned char PY_mb_rou   []={"������������"};
const unsigned char PY_mb_ru    []={"������������������������������޸����"};
const unsigned char PY_mb_ruan  []={"������"};
const unsigned char PY_mb_rui   []={"������������ި"};
const unsigned char PY_mb_run   []={"����"};
const unsigned char PY_mb_ruo   []={"����ټ��"};
const unsigned char PY_mb_sa    []={"����������ئ���"};
const unsigned char PY_mb_sai   []={"������˼����"};
const unsigned char PY_mb_san   []={"��ɢɡ���������"};
const unsigned char PY_mb_sang  []={"ɣɥɤ�����"};
const unsigned char PY_mb_sao   []={"ɨɩɦɧ��ܣ��������"};
const unsigned char PY_mb_se    []={"ɫɬɪ������"};
const unsigned char PY_mb_sen   []={"ɭ"};
const unsigned char PY_mb_seng  []={"ɮ"};
const unsigned char PY_mb_sha   []={"ɱɳɶɴɵɰɲɯ��ɷɼ����������������"};
const unsigned char PY_mb_shai  []={"ɹɸɫ��"};
const unsigned char PY_mb_shan  []={"ɽ��������ɼɾɿ��ɺ����դɻ���������������������۷�������������ڨ������"};
const unsigned char PY_mb_shang []={"���������������������������"};
const unsigned char PY_mb_shao  []={"����������������������������ۿ��������"};
const unsigned char PY_mb_she   []={"�������������������������������������"};
const unsigned char PY_mb_shen  []={"�����������������������������ʲ��������ݷڷ�������������"};
const unsigned char PY_mb_sheng []={"��ʡʣ������ʤʢʥ����������������"};
const unsigned char PY_mb_shi   []={"��ʹʮʱ������ʯʦ��ʷʽʶʭʸʰʺʻʼ����ʾʿ��������������ʲֳ������ʧ������������ʨʳ��ʴ��ʵʩʪʫʬ��ݪ����������������������߱���"};
const unsigned char PY_mb_shou  []={"���������������������������"};
const unsigned char PY_mb_shu   []={"��������������������������������������������������ˡ�������������������"};
const unsigned char PY_mb_shua  []={"ˢˣ�"};
const unsigned char PY_mb_shuai []={"ˤ˦��˧˥�"};
const unsigned char PY_mb_shuan []={"˨˩����"};
const unsigned char PY_mb_shuang[]={"˫˪ˬ����"};
const unsigned char PY_mb_shui  []={"ˮ˭˯˰˵"};
const unsigned char PY_mb_shun  []={"˳˱˲˴"};
const unsigned char PY_mb_shuo  []={"˵��˶˸˷����������"};
const unsigned char PY_mb_si    []={"����˿˺��˽˻˼��˾˹ʳ�Ų���������������������������������������ٹ"};
const unsigned char PY_mb_song  []={"�����������������ݿ�����ڡ����"};
const unsigned char PY_mb_sou   []={"��������������޴�����������"};
const unsigned char PY_mb_su    []={"�����������������������������������������"};
const unsigned char PY_mb_suan  []={"�������"};
const unsigned char PY_mb_sui   []={"���������������������������������ݴ�"};
const unsigned char PY_mb_sun   []={"�������ݥ�����"};
const unsigned char PY_mb_suo   []={"��������������ɯ�����������������"};
const unsigned char PY_mb_ta    []={"������̤������̡̢̣�����������������"};
const unsigned char PY_mb_tai   []={"̧̨̫̬̥̦̩̪̭������߾����޷ۢ��"};
const unsigned char PY_mb_tan   []={"̸̲̾̽��̶̵̷̴̼̯̰̳̺̹̱̮̻̿۰������������"};
const unsigned char PY_mb_tang  []={"�����������������������������������������������"};
const unsigned char PY_mb_tao   []={"����������������������ػ������߶��"};
const unsigned char PY_mb_te    []={"������߯"};
const unsigned char PY_mb_teng  []={"����������"};
const unsigned char PY_mb_ti    []={"���������������������������������������������"};
const unsigned char PY_mb_tian  []={"����������������������������"};
const unsigned char PY_mb_tiao  []={"����������������������٬�������"};
const unsigned char PY_mb_tie   []={"����������"};
const unsigned char PY_mb_ting  []={"��ͣͦ��ͤͧͥ͢��͡���������������"};
const unsigned char PY_mb_tong  []={"ͬͨʹͭͰͲͱͳͯͮͩͫ����ͪ�����������١����"};
const unsigned char PY_mb_tou   []={"ͷ͵͸Ͷ����"};
const unsigned char PY_mb_tu    []={"��ͼ��Ϳ��ͺͻͽ͹;��ܢݱ������"};
const unsigned char PY_mb_tuan  []={"���������"};
const unsigned char PY_mb_tui   []={"��������������߯"};
const unsigned char PY_mb_tun   []={"�������ζ��������"};
const unsigned char PY_mb_tuo   []={"������������������������ر٢����������������������"};
const unsigned char PY_mb_wa    []={"�����������ݰ��������"};
const unsigned char PY_mb_wai   []={"������"};
const unsigned char PY_mb_wan   []={"��������������������������������������ݸ�����ܹ���������"};
const unsigned char PY_mb_wang  []={"��������������������â�������"};
const unsigned char PY_mb_wei   []={"ΪλδΧιθ΢ζβα��ΰ��ΣΥίκΨάηΩΤΡενξΫγοΦήέμ�������������������������������������������ޱ��"};
const unsigned char PY_mb_wen   []={"�����������������������������"};
const unsigned char PY_mb_weng  []={"��������޳"};
const unsigned char PY_mb_wo    []={"������������������������ݫ�����"};
const unsigned char PY_mb_wu    []={"������������������������������������������������������������������أ���������������������������������������"};
const unsigned char PY_mb_xi    []={"��ϴϸ��ϷϵϲϯϡϪϨ��ϥϢϮϧϰ��ϦϤ����ϣϭ������ϱ��ϳϩ����϶��ϫϬ����������������������������������������������ۭ����������������ݾ������"};
const unsigned char PY_mb_xia   []={"������ϿϺϹϼ��ϻ��Ͻ��Ͼ�����������������"};
const unsigned char PY_mb_xian  []={"����������������������������������������������������ϳ����޺���ݲ���������������������������"};
const unsigned char PY_mb_xiang []={"���������������������������ή������������ܼ��������������"};
const unsigned char PY_mb_xiao  []={"СЦ��������Ч����ФТ��Х������У�������������������������"};
const unsigned char PY_mb_xie   []={"дЩЬЪбѪлжЮмзкийШаЭегЫЯв����Ҷ��������ߢ�����������ޯ������"};
const unsigned char PY_mb_xin   []={"��������онп��Ѱ�����ضݷܰ�����"};
const unsigned char PY_mb_xing  []={"������������������������������ʡ�������ߩ��"};
const unsigned char PY_mb_xiong []={"��������������ܺ"};
const unsigned char PY_mb_xiu   []={"�����������������������������������"};
const unsigned char PY_mb_xu    []={"�����������������������������������������������ޣ���������ڼ�������"};
const unsigned char PY_mb_xuan  []={"ѡ������������ѤѣѢȯ������������������������������"};
const unsigned char PY_mb_xue   []={"ѧѩѪѥѨ��Ѧ�������"};
const unsigned char PY_mb_xun   []={"ѰѶѬѵѭѳѮѲѸѱѴѷѫ��ѯ��������ަ޹��������������ۨ�"};
const unsigned char PY_mb_ya    []={"ѽѹ��ѺѿѼ����������Ѿ����ѻ��������������������������"};
const unsigned char PY_mb_yan   []={"����������������������������������������������������������������������������������������������������ٲ۱۳�������������Ǧ����ܾ������"};
const unsigned char PY_mb_yang  []={"������������������������������������������������"};
const unsigned char PY_mb_yao   []={"Ҫҡҩҧ��ҤҨ����ҥңҦ��ҫҢԿ��زسߺ���������������������ű��Լ�"};
const unsigned char PY_mb_ye    []={"ҲҹҵҰҶүҳҺҴҸұҭҮ��ҷҬа��������������"};
const unsigned char PY_mb_yi    []={"һ��������������ҽ������������������������ʳ��������������Ҽ����Ҿҿ�����������ض���β���������������������������������������������������������ܲ����ڱ�����������������������٫���������������߮����������޲߽����"};
const unsigned char PY_mb_yin   []={"����ӡ����������������������������ܧ۴��ط���������������������"};
const unsigned char PY_mb_ying  []={"ӦӲӰӪӭӳӬӮӥӢӱӨӯӤӣӧӫө������������ݺ�۫�������������������"};
const unsigned char PY_mb_yo    []={"Ӵ���"};
const unsigned char PY_mb_yong  []={"��ӿ��ӵӼ��ӺӽӾӶӻӸӹӷ��ٸ��ܭ�����������"};
const unsigned char PY_mb_you   []={"��������������������������������������������٧ݬݯݵ������������������������������"};
const unsigned char PY_mb_yu    []={"������������������������������������������������������������������������������ξ����ԡԢԣԤԥԦε����������������������������������������خ��ٶ��������������������������ع������������"};
const unsigned char PY_mb_yuan  []={"ԶԱԪԺԲԭԸ԰ԮԳԹԩԴԵԬԨԷԫԧԯ��������������ܾ������ܫ��"};
const unsigned char PY_mb_yue   []={"��ԽԼԾ��������Ի˵��Կ����������"};
const unsigned char PY_mb_yun   []={"������������������������Ա�����۩ܿ����������"};
const unsigned char PY_mb_za    []={"����զ����������"};
const unsigned char PY_mb_zai   []={"��������������������"};
const unsigned char PY_mb_zan   []={"���������������������"};
const unsigned char PY_mb_zang  []={"�����߲������"};
const unsigned char PY_mb_zao   []={"������������������������������"};
const unsigned char PY_mb_ze    []={"��������զ�������������������"};
const unsigned char PY_mb_zei   []={"��"};
const unsigned char PY_mb_zen   []={"����"};
const unsigned char PY_mb_zeng  []={"����������������"};
const unsigned char PY_mb_zha   []={"��ը��բգեէ��թ����ա��߸�����������������դզ����"};
const unsigned char PY_mb_zhai  []={"ժխծիկ���լ������"};
const unsigned char PY_mb_zhan  []={"վռսյմճձչջղ��պտ��նշոհ�����"};
const unsigned char PY_mb_zhang []={"���³��������������������������������۵�����"};
const unsigned char PY_mb_zhao  []={"����������צ�׳������س�����������گ��"};
const unsigned char PY_mb_zhe   []={"����������������������������ߡ����������"};
const unsigned char PY_mb_zhen  []={"����������������������������������������������������������"};
const unsigned char PY_mb_zheng []={"��������������֤֢֣��������֡������ں�綡��"};
const unsigned char PY_mb_zhi   []={"ֱֻ֪֮��ָֽ֧֥֦��֨֩��֭֫֬��ְ֯��ֲ��ֳִֵֶַ����ֹֺ��ּ��־ֿ����������ʶ����������������������������ۤ���������������������������������ش�������μ�"};
const unsigned char PY_mb_zhong []={"�����������������������������ڣ��"};
const unsigned char PY_mb_zhou  []={"����������������������������������ݧ����������"};
const unsigned char PY_mb_zhu   []={"ס��������������������������������������������עףפ�����������������������٪�����������ۥ��������"};
const unsigned char PY_mb_zhua  []={"ץצ��"};
const unsigned char PY_mb_zhuai []={"קת"};
const unsigned char PY_mb_zhuan []={"תרש׬��׫׭�������"};
const unsigned char PY_mb_zhuang[]={"װײׯ׳׮״��ױ�����"};
const unsigned char PY_mb_zhui  []={"׷׹׺׶׸׵�������"};
const unsigned char PY_mb_zhun  []={"׼׻�����"};
const unsigned char PY_mb_zhuo  []={"׽������׾����׿��������ߪ��������پ�����"};
const unsigned char PY_mb_zi    []={"��������������֨��������������������������������������������������������"};
const unsigned char PY_mb_zong  []={"����������������������"};
const unsigned char PY_mb_zou   []={"����������۸������"};
const unsigned char PY_mb_zu    []={"����������������������"};
const unsigned char PY_mb_zuan  []={"����׬߬����"};
const unsigned char PY_mb_zui   []={"��������Ѿ���ީ"};
const unsigned char PY_mb_zun   []={"����ߤ����"};
const unsigned char PY_mb_zuo   []={"�������������������������������������"};
const unsigned char PY_mb_bd    []={",.?!:;'\"()<>[]{}$%@*+-_=~`|/\\^&*"};
const unsigned char PY_mb_sz    []={"0123456789"}; //����
const unsigned char PY_mb_abc   []={"abc"};
const unsigned char PY_mb_def   []={"def"};
const unsigned char PY_mb_ghi   []={"ghi"};
const unsigned char PY_mb_jkl   []={"jkl"}; 
const unsigned char PY_mb_mno   []={"mno"};
const unsigned char PY_mb_pqrs  []={"pqrs"}; 
const unsigned char PY_mb_tuv   []={"tuv"};
const unsigned char PY_mb_wxyz  []={"wxyz"}; 
const unsigned char PY_mb_ABC   []={"ABC"};
const unsigned char PY_mb_DEF   []={"DEF"};
const unsigned char PY_mb_GHI   []={"GHI"};
const unsigned char PY_mb_JKL   []={"JKL"}; 
const unsigned char PY_mb_MNO   []={"MNO"};
const unsigned char PY_mb_PQRS  []={"PQRS"}; 
const unsigned char PY_mb_TUV   []={"TUV"};
const unsigned char PY_mb_WXYZ  []={"WXYZ"};

const struct t9PY_index  t9PY_index0[] ={0x00," ",PY_mb_bd};		
//1
const struct t9PY_index  t9PY_index1[] ={0x20," ",PY_mb_space};	//1


const struct t9PY_index  t9PY_index2[] ={{0x2,"a",PY_mb_a},	   //55
{0x22,"ba",PY_mb_ba},
{0x22,"ca",PY_mb_ca},
{0x224,"bai",PY_mb_bai},
{0x224,"cai",PY_mb_cai},
{0x226,"ban",PY_mb_ban},
{0x226,"bao",PY_mb_bao},
{0x226,"can",PY_mb_can},
{0x226,"cao",PY_mb_cao},
{0x226,"cen",PY_mb_cen},
{0x2264,"bang",PY_mb_bang},
{0x2264,"cang",PY_mb_cang},
{0x23,"ce",PY_mb_ce},
{0x234,"bei",PY_mb_bei},
{0x236,"ben",PY_mb_ben},
{0x2364,"beng",PY_mb_beng},
{0x2364,"ceng",PY_mb_ceng},
{0x24,"ai",PY_mb_ai},
{0x24,"bi",PY_mb_bi},
{0x24,"ci",PY_mb_ci},
{0x242,"cha",PY_mb_cha},
{0x2424,"chai",PY_mb_chai},
{0x2426,"bian",PY_mb_bian},
{0x2426,"biao",PY_mb_biao},
{0x2426,"chan",PY_mb_chan},
{0x2426,"chao",PY_mb_chao},
{0x24264,"chang",PY_mb_chang},
{0x243,"bie",PY_mb_bie},
{0x243,"che",PY_mb_che},
{0x2436,"chen",PY_mb_chen},
{0x24364,"cheng",PY_mb_cheng},
{0x244,"chi",PY_mb_chi},
{0x246,"bin",PY_mb_bin},
{0x2464,"bing",PY_mb_bing},
{0x24664,"chong",PY_mb_chong},
{0x2468,"chou",PY_mb_chou},
{0x248,"chu",PY_mb_chu},
{0x24824,"chuai",PY_mb_chuai},
{0x24826,"chuan",PY_mb_chuan},
{0x248264,"chuang",PY_mb_chuang},
{0x2484,"chui",PY_mb_chui},
{0x2484,"chun",PY_mb_chun},
{0x2486,"chuo",PY_mb_chuo},										
{0x26,"an",PY_mb_an},
{0x26,"ao",PY_mb_ao},                   	
{0x26,"bo",PY_mb_bo},
{0x264,"ang",PY_mb_ang},
{0x2664,"cong",PY_mb_cong},
{0x268,"cou",PY_mb_cou},
{0x28,"bu",PY_mb_bu},
{0x28,"cu",PY_mb_cu},
{0x2826,"cuan",PY_mb_cuan},
{0x284,"cui",PY_mb_cui},
{0x286,"cun",PY_mb_cun},
{0x286,"cuo",PY_mb_cuo}	
};	 
const struct t9PY_index  t9PY_index3[] ={{0x03,"e",PY_mb_e},		//33
{0x32,"da",PY_mb_da},
{0x32,"fa",PY_mb_fa},
{0x324,"dai",PY_mb_dai},
{0x326,"dan",PY_mb_dan},
{0x326,"dao",PY_mb_dao},
{0x326,"fan",PY_mb_fan}, 
{0x3264,"dang",PY_mb_dang},
{0x3264,"fang",PY_mb_fang},										 
{0x33,"de",PY_mb_de},
{0x334,"fei",PY_mb_fei},
{0x336,"fen",PY_mb_fen},
{0x3364,"deng",PY_mb_deng},
{0x3364,"feng",PY_mb_feng},
{0x34,"di",PY_mb_di},
{0x342,"dia",PY_mb_dia},
{0x3426,"dian",PY_mb_dian},
{0x3426,"diao",PY_mb_diao},
{0x343,"die",PY_mb_die},
{0x3464,"ding",PY_mb_ding},
{0x348,"diu",PY_mb_diu},
{0x36,"en",PY_mb_en},
{0x36,"fo",PY_mb_fo},
{0x3664,"dong",PY_mb_dong},
{0x368,"dou",PY_mb_dou},
{0x368,"fou",PY_mb_fou},										 
{0x37,"er",PY_mb_er},
{0x38,"du",PY_mb_du},
{0x38,"fu",PY_mb_fu},
{0x3826,"duan",PY_mb_duan},
{0x384,"dui",PY_mb_dui},
{0x386,"dun",PY_mb_dun},
{0x386,"duo",PY_mb_duo}                                         
};
const struct t9PY_index  t9PY_index4[] ={{0x42,"ha",PY_mb_ha},	   //38
{0x42,"ga",PY_mb_ga},
{0x423,"hai",PY_mb_hai},
{0x424,"gai",PY_mb_gai},
{0x426,"gan",PY_mb_gan},
{0x426,"gao",PY_mb_gao},
{0x426,"han",PY_mb_han},
{0x426,"hao",PY_mb_hao}, 
{0x4264,"gang",PY_mb_gang},
{0x4264,"hang",PY_mb_hang},
{0x43,"ge",PY_mb_ge},
{0x43,"he",PY_mb_he},
{0x434,"gei",PY_mb_gei},
{0x434,"hei",PY_mb_hei},
{0x436,"gen",PY_mb_gan},
{0x436,"hen",PY_mb_hen},
{0x4364,"geng",PY_mb_geng},
{0x4364,"heng",PY_mb_heng},
{0x4664,"gong",PY_mb_gong},
{0x4664,"hong",PY_mb_hong},
{0x468,"gou",PY_mb_gou},
{0x468,"hou",PY_mb_hou},
{0x48,"gu",PY_mb_gu},
{0x48,"hu",PY_mb_hu},
{0x482,"gua",PY_mb_gua},
{0x482,"hua",PY_mb_hua},
{0x4823,"huai",PY_mb_huai},
{0x4824,"guai",PY_mb_guai},                                         
{0x4826,"guan",PY_mb_guan},
{0x4826,"huan",PY_mb_huan},
{0x48264,"guang",PY_mb_guang},
{0x48264,"huang",PY_mb_huang},
{0x484,"gui",PY_mb_gui},
{0x484,"hui",PY_mb_hui},
{0x486,"gun",PY_mb_gun},
{0x486,"guo",PY_mb_guo},
{0x486,"hun",PY_mb_hun},
{0x486,"huo",PY_mb_huo}
};
const struct t9PY_index  t9PY_index5[] ={{0x52,"ka",PY_mb_ka},	  	//57
{0x52,"la",PY_mb_la},
{0x524,"kai",PY_mb_kai},
{0x524,"lai",PY_mb_lai},                                         
{0x526,"kan",PY_mb_kan},
{0x526,"kao",PY_mb_kao},
{0x526,"lan",PY_mb_lan},
{0x526,"lao",PY_mb_lao},
{0x5264,"kang",PY_mb_kang},
{0x5264,"lang",PY_mb_lang},
{0x53,"ke",PY_mb_ke},
{0x53,"le",PY_mb_le},
{0x534,"lei",PY_mb_lei},
{0x536,"ken",PY_mb_ken},
{0x5364,"keng",PY_mb_keng},
{0x5366,"leng",PY_mb_leng}, 
{0x54,"ji",PY_mb_ji},
{0x54,"li",PY_mb_li},
{0x542,"jia",PY_mb_jia},
{0x542,"lia",PY_mb_lia},
{0x5426,"jian",PY_mb_jian},
{0x5426,"jiao",PY_mb_jiao},
{0x5426,"lian",PY_mb_lian},
{0x5426,"liao",PY_mb_liao},
{0x54264,"jiang",PY_mb_jiang},
{0x54264,"liang",PY_mb_liang},									     
{0x543,"jie",PY_mb_jie},
{0x543,"lie",PY_mb_lie},
{0x546,"jin",PY_mb_jin},
{0x546,"lin",PY_mb_lin},
{0x5464,"jing",PY_mb_jing},
{0x5464,"ling",PY_mb_ling},
{0x54664,"jiong",PY_mb_jiong},
{0x548,"jiu",PY_mb_jiu},
{0x548,"liu",PY_mb_liu},
{0x5664,"kong",PY_mb_kong},
{0x5664,"long",PY_mb_long},
{0x568,"kou",PY_mb_kou},
{0x568,"lou",PY_mb_lou},										 
{0x58,"ju",PY_mb_ju},
{0x58,"ku",PY_mb_ku},
{0x58,"lu",PY_mb_lu},
{0x58,"lv",PY_mb_lv},									     
{0x582,"kua",PY_mb_kua},
{0x5824,"kuai",PY_mb_kuai},
{0x5826,"juan",PY_mb_juan},
{0x5826,"kuan",PY_mb_kuan},
{0x5826,"luan",PY_mb_luan},									                                         
{0x58264,"kuang",PY_mb_kuang},
{0x583,"jue",PY_mb_jue},
{0x583,"lue",PY_mb_lue},
{0x584,"kui",PY_mb_kui},	
{0x586,"jun",PY_mb_jun},
{0x586,"kun",PY_mb_kun},
{0x586,"kuo",PY_mb_kuo},
{0x586,"lun",PY_mb_lun},
{0x586,"luo",PY_mb_luo}
};
const struct t9PY_index  t9PY_index6[] ={{0x06,"o",PY_mb_o},	   //44
{0x62,"ma",PY_mb_ma},
{0x62,"na",PY_mb_na},
{0x624,"mai",PY_mb_mai},
{0x624,"nai",PY_mb_nai},
{0x626,"man",PY_mb_man},
{0x626,"mao",PY_mb_mao},
{0x626,"nan",PY_mb_nan},
{0x626,"nao",PY_mb_nao},
{0x6264,"mang",PY_mb_mang},
{0x6264,"nang",PY_mb_nang},										 
{0x63,"me",PY_mb_me},
{0x63,"ne",PY_mb_ne},
{0x634,"mei",PY_mb_mei},
{0x634,"nei",PY_mb_nei},                                    
{0x636,"men",PY_mb_men},
{0x636,"nen",PY_mb_nen},
{0x6364,"meng",PY_mb_meng},
{0x6364,"neng",PY_mb_neng},
{0x64,"mi",PY_mb_mi},
{0x64,"ni",PY_mb_ni},
{0x6426,"mian",PY_mb_mian},
{0x6426,"miao",PY_mb_miao},
{0x6426,"nian",PY_mb_nian},
{0x6426,"niao",PY_mb_niao},									     
{0x64264,"niang",PY_mb_niang},
{0x643,"mie",PY_mb_mie},
{0x643,"nie",PY_mb_nie},
{0x646,"min",PY_mb_min},
{0x646,"nin",PY_mb_nin},
{0x6464,"ming",PY_mb_ming},
{0x6464,"ning",PY_mb_ning},
{0x648,"miu",PY_mb_miu},
{0x648,"niu",PY_mb_niu},										 
{0x66,"mo",PY_mb_mo},
{0x6664,"nong",PY_mb_nong},
{0x668,"mou",PY_mb_mou},
{0x68,"mu",PY_mb_mu},
{0x68,"nu",PY_mb_nu},
{0x68,"nv",PY_mb_nv},
{0x68,"ou",PY_mb_ou},
{0x6826,"nuan",PY_mb_nuan},
{0x683,"nue",PY_mb_nue},
{0x686,"nuo",PY_mb_nuo}                                         
};
const struct t9PY_index  t9PY_index7[] ={{0x72,"pa",PY_mb_pa},		 //79
{0x72,"sa",PY_mb_sa},
{0x724,"pai",PY_mb_pai},
{0x724,"sai",PY_mb_sai},
{0x726,"pan",PY_mb_pan},
{0x726,"pao",PY_mb_pao},
{0x726,"ran",PY_mb_ran},
{0x726,"rao",PY_mb_rao},
{0x726,"sao",PY_mb_sao},
{0x726,"san",PY_mb_san},
{0x7264,"pang",PY_mb_pang},
{0x7264,"rang",PY_mb_rang},
{0x7264,"sang",PY_mb_sang},
{0x73,"re",PY_mb_re},
{0x73,"se",PY_mb_se},
{0x734,"pei",PY_mb_pei},
{0x736,"pen",PY_mb_pen},
{0x736,"ren",PY_mb_ren},
{0x736,"sen",PY_mb_sen},
{0x7364,"peng",PY_mb_peng},
{0x7364,"reng",PY_mb_reng},
{0x7364,"seng",PY_mb_seng},
{0x74,"pi",PY_mb_pi},
{0x74,"qi",PY_mb_qi},
{0x74,"ri",PY_mb_ri},
{0x74,"si",PY_mb_si},
{0x742,"sha",PY_mb_sha},
{0x742,"qia",PY_mb_qia},
{0x7424,"shai",PY_mb_shai},
{0x7426,"pian",PY_mb_pian},
{0x7426,"piao",PY_mb_piao},
{0x7426,"qian",PY_mb_qian},
{0x7426,"qiao",PY_mb_qiao},
{0x7426,"shan",PY_mb_shan},
{0x7426,"shao",PY_mb_shao},
{0x74264,"qiang",PY_mb_qiang},
{0x74264,"shang",PY_mb_shang},
{0x743,"qie",PY_mb_qie},
{0x743,"pie",PY_mb_pie},
{0x743,"she",PY_mb_she},
{0x7436,"shen",PY_mb_shen},
{0x74364,"sheng",PY_mb_sheng},
{0x744,"shi",PY_mb_shi},								
{0x746,"pin",PY_mb_pin},
{0x746,"qin",PY_mb_qin},
{0x7464,"ping",PY_mb_ping},                                   
{0x7464,"qing",PY_mb_qing},
{0x74664,"qiong",PY_mb_qiong},
{0x7468,"shou",PY_mb_shou},
{0x748,"qiu",PY_mb_qiu},
{0x748,"shu",PY_mb_shu},
{0x7482,"shua",PY_mb_shua},
{0x74824,"shuai",PY_mb_shuai},
{0x74826,"shuan",PY_mb_shuan},
{0x748264,"shuang",PY_mb_shuang},
{0x7484,"shui",PY_mb_shui},
{0x7486,"shun",PY_mb_shun},
{0x7486,"shuo",PY_mb_shuo},
{0x76,"po",PY_mb_po},
{0x7664,"rong",PY_mb_rong},
{0x7664,"song",PY_mb_song},
{0x768,"pou",PY_mb_pou},                                         
{0x768,"rou",PY_mb_rou},
{0x768,"sou",PY_mb_sou},
{0x78,"pu",PY_mb_pu},
{0x78,"qu",PY_mb_qu},
{0x78,"ru",PY_mb_ru},
{0x78,"su",PY_mb_su},
{0x7826,"quan",PY_mb_quan},
{0x7826,"ruan",PY_mb_ruan},
{0x7826,"suan",PY_mb_suan},
{0x783,"que",PY_mb_que},
{0x784,"rui",PY_mb_rui},
{0x784,"sui",PY_mb_sui},									
{0x786,"qun",PY_mb_qun},
{0x786,"run",PY_mb_run},
{0x786,"ruo",PY_mb_ruo},
{0x786,"sun",PY_mb_sun},
{0x786,"suo",PY_mb_suo}                                   
};
const struct t9PY_index  t9PY_index8[] ={{0x82,"ta",PY_mb_ta},	 //19
{0x824,"tai",PY_mb_tai},
{0x826,"tan",PY_mb_tan},                                         
{0x826,"tao",PY_mb_tao},
{0x8264,"tang",PY_mb_tang},
{0x83,"te",PY_mb_te},
{0x8364,"teng",PY_mb_teng},
{0x84,"ti",PY_mb_ti},
{0x8426,"tian",PY_mb_tian},
{0x8426,"tiao",PY_mb_tiao},
{0x843,"tie",PY_mb_tie},
{0x8464,"ting",PY_mb_ting},
{0x8664,"tong",PY_mb_tong},
{0x868,"tou",PY_mb_tou},
{0x88,"tu",PY_mb_tu},
{0x8826,"tuan",PY_mb_tuan},
{0x884,"tui",PY_mb_tui},
{0x886,"tun",PY_mb_tun},
{0x886,"tuo",PY_mb_tuo}                                         
};
const struct t9PY_index  t9PY_index9[] ={{0x92,"wa",PY_mb_wa},	  //74
{0x92,"ya",PY_mb_ya},
{0x92,"za",PY_mb_za},
{0x924,"wai",PY_mb_wai},
{0x924,"zai",PY_mb_zai},
{0x926,"wan",PY_mb_wan},
{0x926,"yan",PY_mb_yan},
{0x926,"yao",PY_mb_yao},
{0x926,"zan",PY_mb_zan},
{0x926,"zao",PY_mb_zao},
{0x9264,"wang",PY_mb_wang},
{0x9264,"yang",PY_mb_yang},
{0x9264,"zang",PY_mb_zang},
{0x93,"ye",PY_mb_ye},
{0x93,"ze",PY_mb_ze},
{0x934,"wei",PY_mb_wei},
{0x934,"zei",PY_mb_zei},
{0x936,"wen",PY_mb_wen},
{0x936,"zen",PY_mb_zen},
{0x9364,"weng",PY_mb_weng},
{0x9364,"zeng",PY_mb_zeng},
{0x94,"xi",PY_mb_xi},
{0x94,"yi",PY_mb_yi},
{0x94,"zi",PY_mb_zi},
{0x942,"xia",PY_mb_xia},
{0x942,"zha",PY_mb_zha},
{0x9424,"zhai",PY_mb_zhai},
{0x9426,"xian",PY_mb_xian},
{0x9426,"xiao",PY_mb_xiao},
{0x9426,"zhan",PY_mb_zhan},
{0x9426,"zhao",PY_mb_zhao},
{0x94264,"xiang",PY_mb_xiang},
{0x94264,"zhang",PY_mb_zhang},
{0x943,"xie",PY_mb_xie},
{0x943,"zhe",PY_mb_zhe},
{0x9436,"zhen",PY_mb_zhen},
{0x94364,"zheng",PY_mb_zheng},
{0x944,"zhi",PY_mb_zhi},
{0x946,"xin",PY_mb_xin},
{0x946,"yin",PY_mb_yin},
{0x9464,"xing",PY_mb_xing},
{0x9464,"ying",PY_mb_ying},
{0x94664,"xiong",PY_mb_xiong},
{0x94664,"zhong",PY_mb_zhong},
{0x9468,"zhou",PY_mb_zhou},
{0x948,"xiu",PY_mb_xiu},
{0x948,"zhu",PY_mb_zhu},
{0x9482,"zhua",PY_mb_zhua},
{0x94824,"zhuai",PY_mb_zhuai},
{0x94826,"zhuan",PY_mb_zhuan},
{0x948264,"zhuang",PY_mb_zhuang},
{0x9484,"zhui",PY_mb_zhui},
{0x9486,"zhun",PY_mb_zhun},
{0x9486,"zhuo",PY_mb_zhuo},
{0x96,"wo",PY_mb_wo},
{0x96,"yo",PY_mb_yo},
{0x9664,"yong",PY_mb_yong},
{0x9664,"zong",PY_mb_zong},
{0x968,"you",PY_mb_you},
{0x968,"zou",PY_mb_zou},
{0x98,"wu",PY_mb_wu},
{0x98,"xu",PY_mb_xu},
{0x98,"yu",PY_mb_yu},
{0x98,"zu",PY_mb_zu},									
{0x9826,"xuan",PY_mb_xuan},
{0x9826,"yuan",PY_mb_yuan},
{0x9826,"zuan",PY_mb_zuan},
{0x983,"xue",PY_mb_xue},
{0x983,"yue",PY_mb_yue},
{0x984,"zui",PY_mb_zui},
{0x986,"xun",PY_mb_xun},
{0x986,"yun",PY_mb_yun},
{0x986,"zun",PY_mb_zun},
{0x986,"zuo",PY_mb_zuo}
};


const struct t9PY_index  t9PY_sz[] ={{0x00,"0",&PY_mb_sz[0]},
{0x01,"1",&PY_mb_sz[1]},
{0x02,"2",&PY_mb_sz[2]},
{0x03,"3",&PY_mb_sz[3]},
{0x04,"4",&PY_mb_sz[4]},
{0x05,"5",&PY_mb_sz[5]},
{0x06,"6",&PY_mb_sz[6]},
{0x07,"7",&PY_mb_sz[7]},
{0x08,"8",&PY_mb_sz[8]},
{0x09,"9",&PY_mb_sz[9]}
}; 
const struct t9PY_index  t9PY_abc[] ={{0x00,"",PY_mb_space},
{0x01,"",PY_mb_space},
{0x02,"abc",PY_mb_abc},
{0x03,"def",PY_mb_def},
{0x04,"ghi",PY_mb_ghi},
{0x05,"jkl",PY_mb_jkl},
{0x06,"mno",PY_mb_mno},
{0x07,"pqrs",PY_mb_pqrs},
{0x08,"tuv",PY_mb_tuv},
{0x09,"wxyz",PY_mb_wxyz}	  								 
};
const struct t9PY_index  t9PY_ABC[] ={{0x00,"",PY_mb_space},
{0x01,"",PY_mb_space},
{0x02,"ABC",PY_mb_ABC},
{0x03,"DEF",PY_mb_DEF},
{0x04,"GHI",PY_mb_GHI},
{0x05,"JKL",PY_mb_JKL},
{0x06,"MNO",PY_mb_MNO},
{0x07,"PQRS",PY_mb_PQRS},
{0x08,"TUV",PY_mb_TUV},
{0x09,"WXYZ",PY_mb_WXYZ}	  								 
};
const struct t9PY_index  *t9PY_index_headno[]={t9PY_index0,
t9PY_index1,
t9PY_index2,
t9PY_index3,
t9PY_index4,
t9PY_index5,
t9PY_index6,
t9PY_index7,
t9PY_index8,
t9PY_index9};

#endif
