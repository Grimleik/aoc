
const char *d5_words[] = {"aeixx",
                          "aeixxab",
                          "ugknbfddgicrmopn",
                          "aaa",
                          "jchzalrnumimnmhp",
                          "haegwjzuvuyypxyu",
                          "dvszwmarrgswjxmb"};

const bool d5_ans[] = {
    true, false, true, true, false, false, false,
};

const char *d5_words_p2[] = {
    "aaaa",
    "xyxy",
    "aaa",
    "aaabab",
    "xxyxx",
    "uurcxstgmygtbstg",
    "ieodomkazucvgmuy",
};

const bool d5_ans_p2[] = {
    true, true, false, true, true, false, false,
};

const char *d5_input[] = {
    "zgsnvdmlfuplrubt", "vlhagaovgqjmgvwq", "ffumlmqwfcsyqpss",
    "zztdcqzqddaazdjp", "eavfzjajkjesnlsb", "urrvucyrzzzooxhx",
    "xdwduffwgcptfwad", "orbryxwrmvkrsxsr", "jzfeybjlgqikjcow",
    "mayoqiswqqryvqdi", "iiyrkoujhgpgkcvx", "egcgupjkqwfiwsjl",
    "zbgtglaqqolttgng", "eytquncjituzzhsx", "dtfkgggvqadhqbwb",
    "zettygjpcoedwyio", "rwgwbwzebsnjmtln", "esbplxhvzzgawctn",
    "vnvshqgmbotvoine", "wflxwmvbhflkqxvo", "twdjikcgtpvlctte",
    "minfkyocskvgubvm", "sfxhhdhaopajbzof", "sofkjdtalvhgwpql",
    "uqfpeauqzumccnrc", "tdflsbtiiepijanf", "dhfespzrhecigzqb",
    "xobfthcuuzhvhzpn", "olgjglxaotocvrhw", "jhkzpfcskutwlwge",
    "zurkakkkpchzxjhq", "hekxiofhalvmmkdl", "azvxuwwfmjdpjskj",
    "arsvmfznblsqngvb", "ldhkzhejofreaucc", "adrphwlkehqkrdmo",
    "wmveqrezfkaivvaw", "iyphmphgntinfezg", "blomkvgslfnvspem",
    "cgpaqjvzhbumckwo", "ydhqjcuotkeyurpx", "sbtzboxypnmdaefr",
    "vxrkhvglynljgqrg", "ttgrkjjrxnxherxd", "hinyfrjdiwytetkw",
    "sufltffwqbugmozk", "tohmqlzxxqzinwxr", "jbqkhxfokaljgrlg",
    "fvjeprbxyjemyvuq", "gmlondgqmlselwah", "ubpwixgxdloqnvjp",
    "lxjfhihcsajxtomj", "qouairhvrgpjorgh", "nloszcwcxgullvxb",
    "myhsndsttanohnjn", "zjvivcgtjwenyilz", "qaqlyoyouotsmamm",
    "tadsdceadifqthag", "mafgrbmdhpnlbnks", "aohjxahenxaermrq",
    "ovvqestjhbuhrwlr", "lnakerdnvequfnqb", "agwpwsgjrtcjjikz",
    "lhlysrshsmzryzes", "xopwzoaqtlukwwdu", "xsmfrfteyddrqufn",
    "ohnxbykuvvlbbxpf", "bbdlivmchvzfuhoc", "vtacidimfcfyobhf",
    "tinyzzddgcnmiabd", "tcjzxftqcqrivqhn", "vgnduqyfpokbmzim",
    "revkvaxnsxospyow", "ydpgwxxoxlywxcgi", "wzuxupbzlpzmikel",
    "nscghlafavnsycjh", "xorwbquzmgmcapon", "asmtiycegeobfxrn",
    "eqjzvgkxgtlyuxok", "mmjrskloposgjoqu", "gceqosugbkvytfto",
    "khivvoxkvhrgwzjl", "qtmejuxbafroifjt", "ttmukbmpoagthtfl",
    "bxqkvuzdbehtduwv", "gvblrpzjylanoggj", "cltewhyjxdbmbtqj",
    "fbkgedqvomdipklj", "uxvuplhenqawfcjt", "fkdjmayiawdkycva",
    "gnloqfgbnibzyidh", "kyzorvtopjiyyyqg", "drckpekhpgrioblt",
    "tvhrkmbnpmkkrtki", "khaldwntissbijiz", "aoojqakosnaxosom",
    "xfptccznbgnpfyqw", "moqdwobwhjxhtrow", "chfwivedutskovri",
    "gprkyalfnpljcrmi", "pwyshpwjndasykst", "xuejivogihttzimd",
    "bugepxgpgahtsttl", "zufmkmuujavcskpq", "urybkdyvsrosrfro",
    "isjxqmlxwtqmulbg", "pxctldxgqjqhulgz", "hclsekryiwhqqhir",
    "hbuihpalwuidjpcq", "ejyqcxmfczqfhbxa", "xljdvbucuxnnaysv",
    "irqceqtqwemostbb", "anfziqtpqzqdttnz", "cgfklbljeneeqfub",
    "zudyqkuqqtdcpmuo", "iuvhylvznmhbkbgg", "mpgppmgfdzihulnd",
    "argwmgcvqqkxkrdi", "pdhrfvdldkfihlou", "cbvqnjrvrsnqzfob",
    "lkvovtsqanohzcmm", "vxoxjdyoylqcnyzt", "kurdpaqiaagiwjle",
    "gwklwnazaxfkuekn", "rbaamufphjsjhbdl", "tzbrvaqvizhsisbd",
    "pbcqlbfjvlideiub", "hiwoetbfywaeddtx", "fjirczxtuupfywyf",
    "omeoegeyyospreem", "ozbbpupqpsskvrjh", "pzvcxkvjdiyeyhxa",
    "odclumkenabcsfzr", "npdyqezqdjqaszvm", "yodkwzmrhtexfrqa",
    "rjcmmggjtactfrxz", "mioxfingsfoimual", "aqskaxjjborspfaa",
    "wientdsttkevjtkf", "tdaswkzckmxnfnct", "voucjhzvkkhuwoqk",
    "boaaruhalgaamqmh", "iufzxutxymorltvb", "pfbyvbayvnrpijpo",
    "obztirulgyfthgcg", "ntrenvhwxypgtjwy", "ephlkipjfnjfjrns",
    "pkjhurzbmobhszpx", "gqbnjvienzqfbzvj", "wjelolsrbginwnno",
    "votanpqpccxqricj", "bxyuyiglnmbtvehi", "qyophcjfknbcbjrb",
    "anoqkkbcdropskhj", "tcnyqaczcfffkrtl", "rsvqimuqbuddozrf",
    "meppxdrenexxksdt", "tyfhfiynzwadcord", "wayrnykevdmywycf",
    "mhowloqnppswyzbu", "tserychksuwrgkxz", "xycjvvsuaxsbrqal",
    "fkrdsgaoqdcqwlpn", "vrabcmlhuktigecp", "xgxtdsvpaymzhurx",
    "ciabcqymnchhsxkc", "eqxadalcxzocsgtr", "tsligrgsjtrnzrex",
    "qeqgmwipbspkbbfq", "vzkzsjujltnqwliw", "ldrohvodgbxokjxz",
    "jkoricsxhipcibrq", "qzquxawqmupeujrr", "mizpuwqyzkdbahvk",
    "suupfxbtoojqvdca", "ywfmuogvicpywpwm", "uevmznxmsxozhobl",
    "vjbyhsemwfwdxfxk", "iyouatgejvecmtin", "tcchwpuouypllcxe",
    "lgnacnphdiobdsef", "uoxjfzmdrmpojgbf", "lqbxsxbqqhpjhfxj",
    "knpwpcnnimyjlsyz", "fezotpoicsrshfnh", "dkiwkgpmhudghyhk",
    "yzptxekgldksridv", "pckmzqzyiyzdbcts", "oqshafncvftvwvsi",
    "yynihvdywxupqmbt", "iwmbeunfiuhjaaic", "pkpkrqjvgocvaxjs",
    "ieqspassuvquvlyz", "xshhahjaxjoqsjtl", "fxrrnaxlqezdcdvd",
    "pksrohfwlaqzpkdd", "ravytrdnbxvnnoyy", "atkwaifeobgztbgo",
    "inkcabgfdobyeeom", "ywpfwectajohqizp", "amcgorhxjcybbisv",
    "mbbwmnznhafsofvr", "wofcubucymnhuhrv", "mrsamnwvftzqcgta",
    "tlfyqoxmsiyzyvgv", "ydceguvgotylwtea", "btyvcjqhsygunvle",
    "usquiquspcdppqeq", "kifnymikhhehgote", "ybvkayvtdpgxfpyn",
    "oulxagvbavzmewnx", "tvvpekhnbhjskzpj", "azzxtstaevxurboa",
    "nfmwtfgrggmqyhdf", "ynyzypdmysfwyxgr", "iaobtgubrcyqrgmk",
    "uyxcauvpyzabbzgv", "fbasfnwiguasoedc", "mgmjoalkbvtljilq",
    "szgkxiqkufdvtksb", "xgfzborpavdmhiuj", "hmuiwnsonvfgcrva",
    "zolcffdtobfntifb", "mvzgcsortkugvqjr", "pbbpgraaldqvzwhs",
    "zvsxegchksgnhpuv", "kdpdboaxsuxfswhx", "jdfggigejfupabth",
    "tpeddioybqemyvqz", "mxsntwuesonybjby", "tzltdsiojfvocige",
    "ubtdrneozoejiqrv", "fusyucnhncoxqzql", "nlifgomoftdvkpby",
    "pyikzbxoapffbqjw", "hzballplvzcsgjug", "ymjyigsfehmdsvgz",
    "vpqgyxknniunksko", "ffkmaqsjxgzclsnq", "jcuxthbedplxhslk",
    "ymlevgofmharicfs", "nyhbejkndhqcoisy", "rjntxasfjhnlizgm",
    "oqlnuxtzhyiwzeto", "tntthdowhewszitu", "rmxyoceuwhsvfcua",
    "qpgsjzwenzbxyfgw", "sumguxpdkocyagpu", "ymfrbxwrawejkduu",
    "hetgrtmojolbmsuf", "qzqizpiyfasgttex", "qnmoemcpuckzsshx",
    "ddyqiihagcmnxccu", "oirwxyfxxyktgheo", "phpaoozbdogbushy",
    "uctjdavsimsrnvjn", "aurbbphvjtzipnuh", "hpbtrubopljmltep",
    "pyyvkthqfsxqhrxg", "jdxaiqzkepxbfejk", "ukgnwbnysrzvqzlw",
    "lfkatkvcssnlpthd", "ucsyecgshklhqmsc", "rwdcbdchuahkvmga",
    "rxkgqakawgpwokum", "hbuyxeylddfgorgu", "tbllspqozaqzglkz",
    "rqfwizjlbwngdvvi", "xuxduyzscovachew", "kouiuxckkvmetvdy",
    "ycyejrpwxyrweppd", "trctlytzwiisjamx", "vtvpjceydunjdbez",
    "gmtlejdsrbfofgqy", "jgfbgtkzavcjlffj", "tyudxlpgraxzchdk",
    "gyecxacqitgozzgd", "rxaocylfabmmjcvt", "tornfzkzhjyofzqa",
    "kocjcrqcsvagmfqv", "zfrswnskuupivzxb", "cunkuvhbepztpdug",
    "pmpfnmklqhcmrtmf", "tfebzovjwxzumxap", "xpsxgaswavnzkzye",
    "lmwijdothmxclqbr", "upqxhmctbltxkarl", "axspehytmyicthmq",
    "xdwrhwtuooikehbk", "tpggalqsytvmwerj", "jodysbwnymloeqjf",
    "rxbazvwuvudqlydn", "ibizqysweiezhlqa", "uexgmotsqjfauhzp",
    "ldymyvumyhyamopg", "vbxvlvthgzgnkxnf", "pyvbrwlnatxigbrp",
    "azxynqididtrwokb", "lwafybyhpfvoawto", "ogqoivurfcgspytw",
    "cinrzzradwymqcgu", "sgruxdvrewgpmypu", "snfnsbywuczrshtd",
    "xfzbyqtyxuxdutpw", "fmpvjwbulmncykbo", "ljnwoslktrrnffwo",
    "ceaouqquvvienszn", "yjomrunrxjyljyge", "xpmjsapbnsdnbkdi",
    "uetoytptktkmewre", "eixsvzegkadkfbua", "afaefrwhcosurprw",
    "bwzmmvkuaxiymzwc", "gejyqhhzqgsrybni", "gjriqsfrhyguoiiw",
    "gtfyomppzsruhuac", "ogemfvmsdqqkfymr", "jgzbipsygirsnydh",
    "zghvlhpjnvqmocgr", "ngvssuwrbtoxtrka", "ietahyupkbuisekn",
    "gqxqwjizescbufvl", "eiprekzrygkncxzl", "igxfnxtwpyaamkxf",
    "soqjdkxcupevbren", "fspypobyzdwstxak", "qstcgawvqwtyyidf",
    "gsccjacboqvezxvd", "bfsblokjvrqzphmc", "srezeptvjmncqkec",
    "opmopgyabjjjoygt", "msvbufqexfrtecbf", "uiaqweyjiulplelu",
    "pbkwhjsibtwjvswi", "xwwzstmozqarurrq", "nytptwddwivtbgyq",
    "ejxvsufbzwhzpabr", "jouozvzuwlfqzdgh", "gfgugjihbklbenrk",
    "lwmnnhiuxqsfvthv", "bzvwbknfmaeahzhi", "cgyqswikclozyvnu",
    "udmkpvrljsjiagzi", "zzuhqokgmisguyna", "ekwcdnjzuctsdoua",
    "eueqkdrnzqcaecyd", "lnibwxmokbxhlris", "fdrbftgjljpzwhea",
    "iabvuhhjsxmqfwld", "qgogzkynrgejakta", "mfcqftytemgnpupp",
    "klvhlhuqhosvjuqk", "gdokmxcgoqvzvaup", "juududyojcazzgvr",
    "fyszciheodgmnotg", "yfpngnofceqfvtfs", "cahndkfehjumwavc",
    "dxsvscqukljxcqyi", "cqukcjtucxwrusji", "vevmmqlehvgebmid",
    "ahswsogfrumzdofy", "ftasbklvdquaxhxb", "tsdeumygukferuif",
    "ybfgbwxaaitpwryg", "djyaoycbymezglio", "trzrgxdjqnmlnzpn",
    "rumwchfihhihpqui", "ffrvnsgrnzemksif", "oizlksxineqknwzd",
    "cirqcprftpjzrxhk", "zrhemeqegmzrpufd", "kqgatudhxgzlgkey",
    "syjugymeajlzffhq", "nlildhmgnwlopohp", "flcszztfbesqhnyz",
    "ohzicmqsajyqptrw", "ebyszucgozsjbelq", "enxbgvvcuqeloxud",
    "ubwnvecbsmhkxwuk", "noifliyxvlkqphbo", "hazlqpetgugxxsiz",
    "ihdzoerqwqhgajzb", "ivrdwdquxzhdrzar", "synwycdvrupablib",
    "mqkdjkntblnmtvxj", "qmmvoylxymyovrnq", "pjtuxskkowutltlq",
    "gchrqtloggkrjciz", "namzqovvsdipazae", "yfokqhkmakyjzmys",
    "iapxlbuoiwqfnozm", "fbcmlcekgfdurqxe", "ednzgtczbplwxjlq",
    "gdvsltzpywffelsp", "oaitrrmpqdvduqej", "gseupzwowmuuibjo",
    "dfzsffsqpaqoixhh", "tclhzqpcvbshxmgx", "cfqkptjrulxiabgo",
    "iraiysmwcpmtklhf", "znwjlzodhktjqwlm", "lcietjndlbgxzjht",
    "gdkcluwjhtaaprfo", "vbksxrfznjzwvmmt", "vpfftxjfkeltcojl",
    "thrmzmeplpdespnh", "yafopikiqswafsit", "xxbqgeblfruklnhs",
    "qiufjijzbcpfdgig", "ikksmllfyvhyydmi", "sknufchjdvccccta",
    "wpdcrramajdoisxr", "grnqkjfxofpwjmji", "lkffhxonjskyccoh",
    "npnzshnoaqayhpmb", "fqpvaamqbrnatjia", "oljkoldhfggkfnfc",
    "ihpralzpqfrijynm", "gvaxadkuyzgbjpod", "onchdguuhrhhspen",
    "uefjmufwlioenaus", "thifdypigyihgnzo", "ugqblsonqaxycvkg",
    "yevmbiyrqdqrmlbw", "bvpvwrhoyneorcmm", "gbyjqzcsheaxnyib",
    "knhsmdjssycvuoqf", "nizjxiwdakpfttyh", "nwrkbhorhfqqoliz",
    "ynsqwvwuwzqpzzwp", "yitscrgexjfclwwh", "dhajwxqdbtrfltzz",
    "bmrfylxhthiaozpv", "frvatcvgknjhcndw", "xlvtdmpvkpcnmhya",
    "pxpemuzuqzjlmtoc", "dijdacfteteypkoq", "knrcdkrvywagglnf",
    "fviuajtspnvnptia", "xvlqzukmwbcjgwho", "bazlsjdsjoeuvgoz",
    "nslzmlhosrjarndj", "menvuwiuymknunwm", "uavfnvyrjeiwqmuu",
    "yrfowuvasupngckz", "taevqhlrcohlnwye", "skcudnogbncusorn",
    "omtnmkqnqedsajfv", "yqmgsqdgsuysqcts", "odsnbtyimikkbmdd",
    "vuryaohxdvjllieb", "dhaxldeywwsfamlo", "opobvtchezqnxpak",
    "pzfnegouvsrfgvro", "rzkcgpxdslzrdktu", "ksztdtqzxvhuryam",
    "ctnqnhkcooqipgkh", "pyqbbvrzdittqbgm", "koennvmolejeftij",
    "rvzlreqikqlgyczj", "xrnujfoyhonzkdgd", "mmsmhkxaiqupfjil",
    "ypjwoemqizddvyfd", "qgugcxnbhvgahykj", "cviodlsrtimbkgmy",
    "xbfbbechhmrjxhnw", "psuipaoucfczfxkp", "hdhwcpeuptgqqvim",
    "gsxlruhjeaareilr", "vgyqonnljuznyrhk", "eewezahlumervpyu",
    "iiolebrxfadtnigy", "tdadlrodykrdfscn", "ocvdtzjxrhtjurpo",
    "gidljbuvuovkhhrf", "qwfcpilbjwzboohd", "xzohxonlezuiupbg",
    "vslpbkkqgvgbcbix", "pivzqrzfxosbstzn", "fyqcfboevcqmbhhs",
    "yqsrneacnlxswojx", "heicqpxxyrwcbsjz", "yzynmnnoumkmlbeh",
    "bncadbjdvvmczylw", "hlnjskgfzbgmigfn", "fphpszymugpcykka",
    "zbifcktanxpmufvy", "saklpkhoyfeqbguy", "nqtqfcfxmpivnjyo",
    "locygrwerxlsvzqm", "qqflecydqvlogjme", "njklmixvgkzpgppf",
    "ugzkpjwjflaswyma", "lriousvkbeftslcy", "nsvsauxzfbbotgmh",
    "tblcpuhjyybrlica", "hqwshxcilwtmxrsf", "xojwroydfeoqupup",
    "tikuzsrogpnohpib", "layenyqgxdfggloc", "nqsvjvbrpuxkqvmq",
    "ivchgxkdlfjdzxmk", "uoghiuosiiwiwdws", "twsgsfzyszsfinlc",
    "waixcmadmhtqvcmd", "zkgitozgrqehtjkw", "xbkmyxkzqyktmpfi",
    "qlyapfmlybmatwxn", "ntawlvcpuaebuypf", "clhebxqdkcyndyof",
    "nrcxuceywiklpemc", "lmurgiminxpapzmq", "obalwqlkykzflxou",
    "huvcudpiryefbcye", "zlxbddpnyuyapach", "gqfwzfislmwzyegy",
    "jhynkjtxedmemlob", "hmrnvjodnsfiukex", "pstmikjykzyavfef",
    "wuwpnscrwzsyalyt", "hksvadripgdgwynm", "tvpfthzjleqfxwkh",
    "xpmrxxepkrosnrco", "qjkqecsnevlhqsly", "jjnrfsxzzwkhnwdm",
    "pehmzrzsjngccale", "bsnansnfxduritrr", "ejzxkefwmzmbxhlb",
    "pceatehnizeujfrs", "jtidrtgxopyeslzl", "sytaoidnamfwtqcr",
    "iabjnikomkgmyirr", "eitavndozoezojsi", "wtsbhaftgrbqfsmm",
    "vvusvrivsmhtfild", "qifbtzszfyzsjzyx", "ifhhjpaqatpbxzau",
    "etjqdimpyjxiuhty", "fvllmbdbsjozxrip", "tjtgkadqkdtdlkpi",
    "xnydmjleowezrecn", "vhcbhxqalroaryfn", "scgvfqsangfbhtay",
    "lbufpduxwvdkwhmb", "tshipehzspkhmdoi", "gtszsebsulyajcfl",
    "dlrzswhxajcivlgg", "kgjruggcikrfrkrw", "xxupctxtmryersbn",
    "hljjqfjrubzozxts", "giaxjhcwazrenjzs", "tyffxtpufpxylpye",
    "jfugdxxyfwkzqmgv", "kbgufbosjghahacw", "xpbhhssgegmthwxb",
    "npefofiharjypyzk", "velxsseyxuhrpycy", "sglslryxsiwwqzfw",
    "susohnlpelojhklv", "lfnpqfvptqhogdmk", "vtcrzetlekguqyle",
    "jlyggqdtamcjiuxn", "olxxqfgizjmvigvl", "cyypypveppxxxfuq",
    "hewmxtlzfqoqznwd", "jzgxxybfeqfyzsmp", "xzvvndrhuejnzesx",
    "esiripjpvtqqwjkv", "xnhrwhjtactofwrd", "knuzpuogbzplofqx",
    "tihycsdwqggxntqk", "xkfywvvugkdalehs", "cztwdivxagtqjjel",
    "dsaslcagopsbfioy", "gmowqtkgrlqjimbl", "ctcomvdbiatdvbsd",
    "gujyrnpsssxmqjhz", "nygeovliqjfauhjf", "mmgmcvnuppkbnonz",
    "bhipnkoxhzcotwel", "wkwpgedgxvpltqid", "mliajvpdocyzcbot",
    "kqjhsipuibyjuref", "zqdczykothbgxwsy", "koirtljkuqzxioaz",
    "audpjvhmqzvhzqas", "cxyhxlhntyidldfx", "iasgocejboxjgtkx",
    "abehujmqotwcufxp", "fmlrzqmazajxeedl", "knswpkekbacuxfby",
    "yvyalnvrxgstqhxm", "sjnrljfrfuyqfwuw", "ssaqruwarlvxrqzm",
    "iaxbpeqqzlcwfqjz", "uwyxshjutkanvvsc", "uxwrlwbblcianvnb",
    "nodtifgrxdojhneh", "mloxjfusriktxrms", "lkfzrwulbctupggc",
    "gcrjljatfhitcgfj", "tkdfxeanwskaivqs", "ypyjxqtmitwubbgt",
    "ssxbygzbjsltedjj", "zdrsnoorwqfalnha", "xlgmissaiqmowppd",
    "azhbwhiopwpguiuo", "fydlahgxtekbweet", "qtaveuqpifprdoiy",
    "kpubqyepxqleucem", "wlqrgqmnupwiuory", "rwyocktuqkuhdwxz",
    "abzjfsdevoygctqv", "zsofhaqqghncmzuw", "lqbjwjqxqbfgdckc",
    "bkhyxjkrqbbunido", "yepxfjnnhldidsjb", "builayfduxbppafc",
    "wedllowzeuswkuez", "gverfowxwtnvgrmo", "tpxycfumxdqgntwf",
    "lqzokaoglwnfcolw", "yqsksyheyspmcdqt", "vufvchcjjcltwddl",
    "saeatqmuvnoacddt", "dxjngeydvsjbobjs", "ucrcxoakevhsgcep",
    "cajgwjsfxkasbayt", "hknzmteafsfemwuv", "xxwhxwiinchqqudr",
    "usfenmavvuevevgr", "kxcobcwhsgyizjok", "vhqnydeboeunnvyk",
    "bgxbwbxypnxvaacw", "bwjzdypacwgervgk", "rrioqjluawwwnjcr",
    "fiaeyggmgijnasot", "xizotjsoqmkvhbzm", "uzphtrpxwfnaiidz",
    "kihppzgvgyoncptg", "hfbkfrxwejdeuwbz", "zgqthtuaqyrxicdy",
    "zitqdjnnwhznftze", "jnzlplsrwovxlqsn", "bmwrobuhwnwivpca",
    "uuwsvcdnoyovxuhn", "nmfvoqgoppoyosaj", "hxjkcppaisezygpe",
    "icvnysgixapvtoos", "vbvzajjgrmjygkhu", "jinptbqkyqredaos",
    "dpmknzhkhleawfvz", "ouwwkfhcedsgqqxe", "owroouiyptrijzgv",
    "bewnckpmnbrmhfyu", "evdqxevdacsbfbjb", "catppmrovqavxstn",
    "dqsbjibugjkhgazg", "mkcldhjochtnvvne", "sblkmhtifwtfnmsx",
    "lynnaujghehmpfpt", "vrseaozoheawffoq", "ytysdzbpbazorqes",
    "sezawbudymfvziff", "vrlfhledogbgxbau", "bipdlplesdezbldn",
    "ermaenjunjtbekeo", "eyaedubkthdecxjq", "gbzurepoojlwucuy",
    "rsiaqiiipjlouecx", "beqjhvroixhiemtw", "buzlowghhqbcbdwv",
    "ldexambveeosaimo", "fpyjzachgrhxcvnx", "komgvqejojpnykol",
    "fxebehjoxdujwmfu", "jnfgvheocgtvmvkx", "qmcclxxgnclkuspx",
    "rsbelzrfdblatmzu", "vexzwqjqrsenlrhm", "tnfbkclwetommqmh",
    "lzoskleonvmprdri", "nnahplxqscvtgfwi", "ubqdsflhnmiayzrp",
    "xtiyqxhfyqonqzrn", "omdtmjeqhmlfojfr", "cnimgkdbxkkcnmkb",
    "tapyijgmxzbmqnks", "byacsxavjboovukk", "awugnhcrygaoppjq",
    "yxcnwrvhojpuxehg", "btjdudofhxmgqbao", "nzqlfygiysfuilou",
    "nubwfjdxavunrliq", "vqxmmhsbmhlewceh", "ygavmcybepzfevrp",
    "kgflmrqsvxprkqgq", "iaqyqmcaedscmakk", "cvbojnbfmrawxzkh",
    "jjjrprbnlijzatuw", "lcsudrrfnnggbrmk", "qzgxbiavunawfibc",
    "gnnalgfvefdfdwwg", "nokmiitzrigxavsc", "etzoxwzxqkkhvais",
    "urxxfacgjccieufi", "lqrioqhuvgcotuec", "dydbaeyoypsbftra",
    "hhrotenctylggzaf", "evctqvzjnozpdxzu", "tbpvithmorujxlcp",
    "pllbtcbrtkfpvxcw", "fzyxdqilyvqreowv", "xdleeddxwvqjfmmt",
    "fcldzthqqpbswoin", "sgomzrpjfmvgwlzi", "axjyskmtdjbxpwoz",
    "hcvaevqxsmabvswh", "lfdlsfcwkwicizfk", "isjbwpzdognhoxvm",
    "oqnexibqxlyxpluh", "zqfbgodsfzwgcwuf", "kvmnwruwsjllbldz",
    "kghazimdyiyhmokj", "uiktgpsxpoahofxn", "zkdwawxargcmidct",
    "ftbixlyiprshrjup", "nofhmbxififwroeg", "mcdaqrhplffxrcdt",
    "fbjxnwojcvlawmlb", "rizoftvwfdhiwyac", "eduogrtyhxfwyars",
    "zoikunqxgjwfqqwr", "zxwbbpmvctzezaqh", "nghujwyeabwdqnop",
    "vcxamijpoyyksogn", "jnckdbuteoqlsdae", "jurfqqawafmsiqwv",
    "inepmztrzehfafie", "tznzkyvzodbrtscf", "xewbavjeppflwscl",
    "ucndzsorexjlnplo", "jpxbctscngxgusvu", "mfmygcllauzuoaok",
    "oibkuxhjmhxhhzby", "zjkslwagmeoisunw", "avnnxmopdgvmukuu",
    "jmaargejcwboqhkt", "yacmpeosarsrfkrv", "iqhgupookcaovwgh",
    "ebjkdnxwtikqzufc", "imdhbarytcscbsvb", "ifyibukeffkbqvcr",
    "aloighmyvwybtxhx", "yszqwrutbkiwkxjg", "xyholyzlltjhsuhp",
    "gykhmrwucneoxcrf", "badkdgqrpjzbabet", "sunaucaucykwtkjj",
    "pumqkglgfdhneero", "usgtyuestahlydxq", "xmfhflphzeudjsjm",
    "knywgmclisgpootg", "mtojnyrnvxtweuzb", "uuxufbwfegysabww",
    "vobhwwocqttlbsik", "yuydfezeqgqxqmnd", "wbqgqkwbibiilhzc",
    "sfdmgxsbuzsawush", "ilhbxcfgordyxwvp", "ahqoavuysblnqaeg",
    "plwgtvpgotskmsey", "ewjcmzkcnautrrmp", "tyekgzbznlikcyqj",
    "bqzctiuaxpriuiga", "bimvbfjkiupyqiys", "mpqtbcxfhwymxncw",
    "htemlptvqhharjgb", "mqbsmsruwzzxgcxc", "zjyedjwhnvteuaid",
    "pzoelkoidwglpttc", "efydnsvlfimvwxhx", "gfyhgoeiyjcgfyze",
    "deqtomhwopmzvjlt", "casafubtkoopuaju", "yylsfarntbucfulg",
    "mgjwsormkjsrrxan", "lkkenpupgmjpnqqd", "tegweszyohsoluot",
    "lihsfdwxmxvwdxna", "rrefrjjxerphejwb", "guuazonjoebhymtm",
    "ysofqzmfmyneziki", "lmjgaliatcpduoal", "qzthcpjwtgahbebr",
    "wvakvephyukmpemm", "simxacxxzfoaeddw", "aetgqmiqzxbvbviz",
    "jxlmhdmqggevrxes", "mmuglnjmuddzgaik", "svopsqhtrslgycgc",
    "xnvcsiiqrcjkvecn", "kkvumxtvashxcops", "bduflsdyeectvcgl",
    "vfrxbwmmytjvqnsj", "eeqtdneiyiaiofxw", "crtbgknfacjtwkfl",
    "uuutuoxdsxolpbhd", "lcrztwzreaswovtn", "htorkvnvujmjdqzj",
    "wttzuzvrzlyhfzyf", "oraewznfwgdsnhuk", "rctlkqqvkwbgrcgk",
    "cfehrsrqhzyiwtmz", "kbvxwcumjkhvjpui", "xxlocexbmniiakfo",
    "gtknkkzvykmlqghl", "kcjuxvkuimhwqrtk", "vohekwkuyuoacuww",
    "vorctgughscysyfo", "zmjevqplngzswxyq", "qhswdrhrijnatkyo",
    "joakcwpfggtitizs", "juzlwjijcmtswdtq", "icbyaqohpkemhkip",
    "rpdxgpzxncedmvzh", "rozkmimbqhbhcddv", "wkkypomlvyglpfpf",
    "jcaqyaqvsefwtaya", "ghvmtecoxlebdwnf", "lqrcyiykkkpkxvqt",
    "eqlarfazchmzotev", "vqwndafvmpguggef", "dbfxzrdkkrusmdke",
    "cmjpjjgndozcmefj", "hbrdcwjuyxapyhlo", "mmforetykbosdwce",
    "zynfntqwblbnfqik", "sodwujfwlasznaiz", "yyvrivjiqnxzqkfp",
    "uldbskmmjbqllpnm", "fyhhrmrsukeptynl", "hpfjekktvdkgdkzl",
    "bozhkoekcxzeorob", "uvpptyfrzkvmtoky", "hkhfprmjdpjvfkcb",
    "igxzwktwsqhsivqu", "qceomwysgkcylipb", "cglateoynluyeqgc",
    "xcsdfkpeguxgvpfh", "owjhxlcncdgkqyia", "rpbmrpcesiakqpna",
    "lueszxiourxsmezb", "zelvsowimzkxliwc", "vzxbttoobtvdtkca",
    "pfxvzphzwscqkzsi", "edsjorainowytbzu", "ipsegdaluoiphmnz",
    "mkhueokfpemywvuw", "urxdnumhylpafdlc", "ggluurzavsxkvwkl",
    "ctclphidqgteakox", "tfobosynxsktajuk", "jzrmemhxqmzhllif",
    "eemwekimdfvqslsx", "yjkwpzrbanoaajgq", "rlxghzanuyeimfhx",
    "hozbgdoorhthlqpv", "obkbmflhyanxilnx", "xojrippyxjmpzmsz",
    "ukykmbfheixuviue", "qivlmdexwucqkres", "rmyxxipqkarpjmox",
    "fgaftctbvcvnrror", "raawxozucfqvasru", "dinpjbdfjfizexdh",
    "gybxubwnnbuyvjcr", "qrqitdvyoneqyxcg", "jqzcfggayzyoqteo",
    "cikqpvxizpdbmppm", "stfpldgyhfmucjjv", "slzbcuihmimpduri",
    "aufajwfrsorqqsnl", "iylmzraibygmgmqj", "lcdyfpcqlktudfmu",
    "pmomzzsdpvgkkliw", "zpplirgtscfhbrkj", "mvhyerxfiljlotjl",
    "ofkvrorwwhusyxjx", "xngzmvcgkqfltjpe", "yxfxaqipmysahqqq",
    "sdqafdzgfdjuabup", "qcqajmerahcdgxfv", "xqimrqtupbapawro",
    "qfvkqwidzzrehsbl", "himixxvueksiqfdf", "vgtfqpuzxxmhrvvd",
    "adiioqeiejguaost", "jnzxuycjxvxehbvm", "xedbpxdhphamoodk",
    "jsrioscmwlsfuxrg", "mtsynnfxunuohbnf", "enamqzfzjunnnkpe",
    "uwcvfecunobyhces", "ciygixtgbsccpftq", "ewjgcronizkcsfjy",
    "wztjkoipxsikoimv", "jrgalyvfelwxforw", "imylyalawbqwkrwb",
    "yflwqfnuuvgjsgcj", "wkysyzusldlojoue", "zopllxnidcffcuau",
    "bscgwxuprxaerskj", "zvnvprxxjkhnkkpq", "nejwxbhjxxdbenid",
    "chryiccsebdbcnkc", "guoeefaeafhlgvxh", "nzapxrfrrqhsingx",
    "mkzvquzvqvwsejqs", "kozmlmbchydtxeeo", "keylygnoqhmfzrfp",
    "srwzoxccndoxylxe", "uqjzalppoorosxxo", "potmkinyuqxsfdfw",
    "qkkwrhpbhypxhiun", "wgfvnogarjmdbxyh", "gkidtvepcvxopzuf",
    "atwhvmmdvmewhzty", "pybxizvuiwwngqej", "zfumwnazxwwxtiry",
    "keboraqttctosemx", "vtlzxaqdetbhclib", "wjiecykptzexuayl",
    "ejatfnyjjdawepyk", "mpcrobansyssvmju", "gqukndzganeueabm",
    "ukzscvomorucdnqd", "wfydhtbzehgwfazx", "mtwqdzlephqvxqmx",
    "dltmlfxbjopefibh", "atcfrowdflluqtbi", "vowawlophlxaqonw",
    "vblgdjzvwnocdipw", "uzerzksmkvnlvlhm", "ytjwhpaylohorvxd",
    "siprvfxvnxcdgofz", "cbhjupewcyjhvtgs", "apqtozaofusmfqli",
    "tmssrtlxfouowqnr", "ntutrvwnzzgmokes", "zrsgpwdzokztdpis",
    "nrobvmsxtfmrqdhv", "kadkaftffaziqdze", "yrovbgcyqtlsnoux",
    "modheiwuhntdecqs", "gzhjypwddizemnys", "gaputpwpcsvzxjho",
    "bgmouxwoajgaozau", "oxuapfrjcpyakiwt", "kntwbvhuaahdixzj",
    "epqjdjbnkxdnaccx", "dspltdvznhypykri", "tdrgqmbnagrxdwtt",
    "njfqawzjggmemtbg", "chpemsgwpzjpdnkk", "fpsrobmbqbmigmwk",
    "flxptsrqaazmprnl", "nzdunrxlcbfklshm", "miuwljvtkgzdlbnn",
    "xbhjakklmbhsdmdt", "xwxhsbnrwnegwcov", "pwosflhodjaiexwq",
    "fhgepuluczttfvqh", "tldxcacbvxyamvkt", "gffxatrjglkcehim",
    "tzotkdrpxkucsdps", "wxheftdepysvmzbe", "qfooyczdzoewrmku",
    "rvlwikuqdbpjuvoo", "bcbrnbtfrdgijtzt", "vaxqmvuogsxonlgq",
    "ibsolflngegravgo", "txntccjmqakcoorp", "vrrbmqaxfbarmlmc",
    "dzspqmttgsuhczto", "pikcscjunxlwqtiw", "lwzyogwxqitqfqlv",
    "gsgjsuaqejtzglym", "feyeqguxbgmcmgpp", "gmttebyebdwvprkn",
    "mzuuwbhzdjfdryxu", "fganrbnplymqbzjx", "cvsrbdcvhtxxdmro",
    "scmgkjlkqukoamyp", "fkgrqbyqpqcworqc", "hjsrvkdibdjarxxb",
    "sztzziuqroeidcus", "pxdfvcpvwaddrzwv", "phdqqxleqdjfgfbg",
    "cqfikbgxvjmnfncy"};

bool is_vowel(const char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool d5_strings(const char *str) {
  int vowels = 0;
  int twiceInARow = 0;
  const char *filterOut[] = {"ab", "cd", "pq", "xy"};
  while (*(str + 1)) {
    for (int i = 0; i < (int)ARRAY_COUNT(filterOut); ++i) {
      if (filterOut[i][0] == *str && filterOut[i][1] == *(str + 1))
        return false;
    }
    if (is_vowel(*str)) {
      ++vowels;
    }
    if (*str == *(str + 1)) {
      ++twiceInARow;
    }
    ++str;
  }
  if (is_vowel(*str))
    ++vowels;
  return vowels >= 3 && twiceInARow >= 1;
}

bool d5_strings_p2(const char *str) {
  int rule1 = 0;
  int rule2 = 0;
  char poc = '\0';
  std::map<char, std::set<char>> ngrams;
  while (*(str + 1)) {
    char c0 = *(str++);
    char c1 = *(str);
    // We only check the rules if the [c0][c1]['c2'] c2 is not out of bounds.
    if (c1 != '\0') {
      // Ngram of c0 is only valid if it doesnt overlap.
      if (c0 == c1 && c0 == poc) {
        poc = '\0';
        // } else if(std::find(ngrams[c0].begin(), ngrams[c0].end(), c1) !=
        // ngrams[c0].end()) {
      } else if (ngrams[c0].find(c1) != ngrams[c0].end()) {
        ++rule1;
      } else {
        ngrams[c0].insert(c1);
        poc = c0;
      }
      // Rule 2:
      if (c0 == *(str + 1)) {
        ++rule2;
      }
    }
  }
  return rule1 >= 1 && rule2 >= 1;
}

void d5() {
  for (int i = 0; i < (int)ARRAY_COUNT(d5_ans); ++i)
    CHECK_VALUE(d5_strings(d5_words[i]), d5_ans[i]);

  for (int i = 0; i < (int)ARRAY_COUNT(d5_ans_p2); ++i)
    CHECK_VALUE(d5_strings_p2(d5_words_p2[i]), d5_ans_p2[i]);

  int result = 0;
  for (int i = 0; i < (int)ARRAY_COUNT(d5_input); ++i) {
    if (d5_strings(d5_input[i])) {
      ++result;
    }
  }
  std::cout << "\t1: " << result << std::endl;
  result = 0;

  for (int i = 0; i < (int)ARRAY_COUNT(d5_input); ++i) {
    if (d5_strings_p2(d5_input[i])) {
      ++result;
    }
  }
  std::cout << "\t2: " << result << std::endl;
}