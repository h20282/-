#include <iostream>
#include <windows.h>
#include <bitset>
#include <vector>
#include <map>
using namespace std;
map<char, string> mingTomi;
map<string, char> miToming;
string chars = "jiamgw0851472369";
void inite(){
	for (int i = 0; i < 256; ++i){
		mingTomi[i-128] = string(1, chars[i%16])+string(1, chars[(i/16)%16]);
		miToming[string(1, chars[i%16])+string(1, chars[(i/16)%16])] = i-128;
	}
}
string decrypt(string s) {
	string ret = "";
	char ch = 0;
	for (int i = 1; i < s.size();) {
		string mi(2,'a');
		mi[0] = s[i++];
		mi[1] = s[i++];
		ret += miToming[mi];
	}
	return ret;
}
string encrypt(string s) {
	char ret[s.size()*2+10] = {'$'};
	int len = 0;
	ret[len++] = '$';
	for (int i = 0; i < s.size(); i++){
		ret[len++] = mingTomi[s[i]][0];
		ret[len++] = mingTomi[s[i]][1];
	}
	return string(ret);
}
bool CopyToClipboard(string s) {
	const char* pszData = s.c_str();
	const int nDataLen = s.size();
	if (::OpenClipboard(NULL)) {
		::EmptyClipboard();
		HGLOBAL clipbuffer;
		char* buffer;
		clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, nDataLen + 1);
		buffer = (char*)::GlobalLock(clipbuffer);
		strcpy(buffer, pszData);
		::GlobalUnlock(clipbuffer);
		::SetClipboardData(CF_TEXT, clipbuffer);
		::CloseClipboard();
		return true;
	}
	cout << "copy error" << endl;
	return false;
}
int main() {
	inite();


	cout << decrypt(string("$2gi04g6mma4m")) << endl;
	cout << decrypt(string("$i7iaaa7m5wmmwm4mm87mi08wgw0m9a3m7a4gg0mm083mi01m785mgm0w0gwm3m2mg88gjwjmw0ma2a6g6wjw50gw1w5mgm0w0gma7m")) << endl;
	cout << decrypt(string("$a7iaaaam7maw4a7gwm7mjmgm589mww5mi8ma2am9m6i66606w4m9ggm00m6awmmgma7m")) << endl;
	cout << decrypt(string("$m7iaaamwaw2m288wm81g9g3m8g34674gg8jwgw34671mgmiwia9m207g1wimj02m3aggma4g3m4mm89m1gawgwmwaw2m289ma8gg4wgm482g00m6g9a9267409")) << endl;
	cout << decrypt(string("$g7iaaa8m784mwgg44g8gwgjw0m5a6g4amg2w6gggwmgg6g5aaw7mim404g0mma2amg886ggg9m4a3g8mam7maw4amwmgg4ma5amw0a5mmgmg7m5g7gwwa0mggm5m1gma1a")) << endl;

	string s;
	while (cin >> s) {
		if (s[0] == '$') {
			cout << decrypt(s) << endl;
			CopyToClipboard(decrypt(s));
		}
		else {
			cout << encrypt(s) << endl;
			CopyToClipboard(encrypt(s));
		}
	}
	return 0;
}
