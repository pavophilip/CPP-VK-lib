#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "vklib.h"
#include <curl/curl.h>
#include "jsoncpp/json/json.h"

using namespace std;

string VK::API::api_url = "https://api.vk.com/method/";

VK::API::API(string version, string lang, bool https, string access_token){
	VK::API::version = version;
	VK::API::lang = lang;
	VK::API::https = https ? "1" : "0";
	VK::API::access_token = access_token;
}

Json::Value VK::API::call(string method, map<string, string> data){
	string url = VK::API::api_url + method;

	data.insert(std::pair<string, string>("v", VK::API::version));
	data.insert(std::pair<string, string>("lang", VK::API::lang));
	data.insert(std::pair<string, string>("https", VK::API::https));
	if(!data.count("access_token")) data.insert(std::pair<string, string>("access_token", VK::API::access_token));

	string resp = VK::API::post(url, Utils::data2str(data));

	Json::Value root;
	Json::Reader reader;
	bool parsedSuccess = reader.parse(resp, root, false);
	if(!parsedSuccess){
		root["success"] = false;
		return root;
	}

	if(root["response"].isNull()){
		if(!root["error"].isNull()){
			root["success"] = false;
		}
	}else{
		root["success"] = true;
	}

	return root;
}

string VK::API::post(string url, string data){
	static char errorBuffer[CURL_ERROR_SIZE];
	static string buffer;

	CURL *curl;
    CURLcode result;
    curl = curl_easy_init();
    if (curl){
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, VK::Utils::CURL_WRITER);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		result = curl_easy_perform(curl);
		if (result == CURLE_OK)      
			return buffer;             
		else      
			return errorBuffer; 
	}
	curl_easy_cleanup(curl);
}

VK::User VK::User::parse(Json::Value json){
	VK::User user;
	user.first_name = json["first_name"].asString();
	user.last_name = json["last_name"].asString();
	user.online = json["online"].asBool();
	user.online_mobile = json["online_mobile"].asBool();
	user.photo_50 = json["photo_50"].asString();
	user.photo_100 = json["photo_100"].asString();
	user.photo_200 = json["photo_200"].asString();
	return user;
}

VK::UserFull VK::UserFull::parse(Json::Value json){
	VK::UserFull user;
	user.first_name = json["first_name"].asString();
	user.last_name = json["last_name"].asString();
	user.online = json["online"].asBool();
	user.online_mobile = json["online_mobile"].asBool();
	user.photo_50 = json["photo_50"].asString();
	user.photo_100 = json["photo_100"].asString();
	user.photo_200 = json["photo_200"].asString();

	user.photo_id = json["photo_id"].asString();
	user.verified = json["verified"].asBool();
	user.blacklisted = json["blacklisted"].asBool();
	user.sex = json["sex"].asInt();
	user.bdate = json["last_name"].asString();
	user.city = VK::City::parse(json["city"]);
	user.country = VK::Country::parse(json["country"]);
	user.home_town = json["home_town"].asString();
	user.domain = json["domain"].asString();
	user.has_mobile = json["has_mobile"].asBool();
	user.contacts = VK::UserFull::Contacts::parse(json["contacts"]);
	user.site = json["site"].asString();
	user.education = VK::Education::parse(json["education"]);

	Json::Value universities = json["universities"];
	if(universities.isArray()){
		for(int i = 0; i < universities.size(); i++){
			user.universities.push_back(VK::University::parse(universities[i]));
		}
	}

	Json::Value schools = json["schools"];
	if(schools.isArray()){
		for(int i = 0; i < schools.size(); i++){
			user.schools.push_back(VK::School::parse(schools[i]));
		}
	}

	user.status = json["status"].asString();
	user.last_seen = VK::UserFull::Seen::parse(json["last_seen"]);
	user.followers_count = json["followers_count"].asInt();
	user.common_count = json["common_count"].asInt();

	Json::Value counters = json["counters"];
	if(counters.isObject()){
		for(Json::Value::iterator it = counters.begin(); it !=counters.end(); ++it){
			Json::Value key = it.key();
			Json::Value value = (*it);
			user.counters.insert(std::pair<string, int>(key.asString(), value.asInt()));
		}
	}
	
	return user;
}

VK::City VK::City::parse(Json::Value json){
	VK::City city;
	city.id = json["id"].asInt();
	city.title = json["title"].asString();
	return city;
}

VK::Country VK::Country::parse(Json::Value json){
	VK::Country country;
	country.id = json["id"].asInt();
	country.title = json["title"].asString();
	return country;
}

VK::Education VK::Education::parse(Json::Value json){
	VK::Education education;
	education.university = json["university"].asInt();
	education.university_name = json["university_name"].asString();
	education.faculty = json["faculty"].asInt();
	education.faculty_name = json["faculty_name"].asString();
	education.graduation = json["graduation"].asInt();
	return education;
}

VK::University VK::University::parse(Json::Value json){
	VK::University university;
	university.id = json["id"].asInt();
	university.country = json["country"].asInt();
	university.city = json["city"].asInt();
	university.name = json["name"].asString();
	university.faculty = json["faculty"].asInt();
	university.faculty_name = json["faculty"].asString();
	university.chair = json["chair"].asInt();
	university.faculty_name = json["faculty"].asString();
	university.chair = json["chair"].asInt();
	university.chair_name = json["chair_name"].asString();
	university.graduation = json["graduation"].asInt();
	return university;
}

VK::School VK::School::parse(Json::Value json){
	VK::School school;
	school.id = json["id"].asInt();
	school.country = json["country"].asInt();
	school.city = json["city"].asInt();
	school.name = json["name"].asString();
	school.year_from = json["year_from"].asInt();
	school.year_to = json["year_to"].asInt();
	school.year_graduated = json["year_graduated"].asInt();
	school.class_l = json["class"].asString();
	school.speciality = json["speciality"].asString();
	school.type = json["type"].asInt();
	school.type_str = json["type_str"].asString();
	return school;
}


VK::UserFull::Contacts VK::UserFull::Contacts::parse(Json::Value json){
	VK::UserFull::Contacts contacts;
	contacts.mobile_phone = json["mobile_phone"].asString();
	contacts.home_phone = json["home_phone"].asString();
	return contacts;
}

VK::UserFull::Seen VK::UserFull::Seen::parse(Json::Value json){
	VK::UserFull::Seen seen;
	seen.time = json["time"].asInt64();
	seen.platform = json["platform"].asInt();
	return seen;
}

// HTTP 
string VK::Utils::char2hex( char dec ){
    char dig1 = (dec&0xF0)>>4;
    char dig2 = (dec&0x0F);
    if ( 0<= dig1 && dig1<= 9) dig1+=48;
    if (10<= dig1 && dig1<=15) dig1+=97-10;
    if ( 0<= dig2 && dig2<= 9) dig2+=48;
    if (10<= dig2 && dig2<=15) dig2+=97-10;
 
    string r;
    r.append( &dig1, 1);
    r.append( &dig2, 1);
    return r;
}

string VK::Utils::urlencode(const string &c){
    string escaped="";
    int max = c.length();
    for(int i=0; i<max; i++){
        if ( (48 <= c[i] && c[i] <= 57) ||
             (65 <= c[i] && c[i] <= 90) ||
             (97 <= c[i] && c[i] <= 122) || 
             (c[i]=='~' || c[i]=='!' || c[i]=='*' || c[i]=='(' || c[i]==')' || c[i]=='\'')
        )
		escaped.append( &c[i], 1);
        else{
            escaped.append("%");
            escaped.append( char2hex(c[i]) );
        }
    }
    return escaped;
}

string VK::Utils::data2str(map<string, string> data){
	string poststring="";
	map<string, string>::iterator curr,end;
    for(curr = data.begin(), end = data.end(); curr != end; curr++){
        poststring+= curr->first + "=" + urlencode(curr->second)+ "&";
    }
	return poststring;
}


int VK::Utils::CURL_WRITER(char *data, size_t size, size_t nmemb, string *buffer){
	int result = 0;
	if (buffer != NULL){
		buffer->append(data, size * nmemb);
		result = size * nmemb;
	}
	return result;
}