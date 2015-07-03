/*!
	@file
	@brief Header file
	@author Philip Pavo

	Contains classes for working with VK API
*/
#include <string>
#include <map> 
#include <vector>
#include "jsoncpp/json/json.h"
#ifndef VKLIB_H
#define VKLIB_H

using namespace std;

/**
	@brief Main namespace
	@author Philip Pavo
*/
namespace VK{
	/**
		@brief Root class for all VK models
	*/
	class Model{
		public:
			Model parse();
	};

	/**
		A City class describes a city.
	*/
	class City: public Model{
		public:
			int id;
			string title;

			int getId();
			static City parse(Json::Value);
	};
	/**
		A Country class describes a country.
	*/
	class Country: public Model{
		public:
			int id;
			string title;

			int getId();
			static Country parse(Json::Value);
	};

	/**
		A Education class describes a education of user
	*/
	class Education: public Model{
	public: 
		int university;
		string university_name;
		int faculty;
		string faculty_name;
		int graduation;

		/**
			Parse Education object from Json Value object

			@param json Json Value Object
			@return Education object
		*/
		static Education parse(Json::Value json);
	};

	/**
		A University class describes a university
	*/
	class University: public Model{
	public:
		int id;
		int country;
		int city;
		string name;
		int faculty;
		string faculty_name;
		int chair;
		string chair_name;
		int graduation;

		/**
			Parse University object from Json Value object

			@param json Json Value Object
			@return University object
		*/
		static University parse(Json::Value json);
	};
	
	/**
		A School class describes a school
	*/
	class School: public Model{
	public:
		int id;
		int country;
		int city;
		string name;
		int year_from;
		int year_to;
		int year_graduated;
		string class_l;
		string speciality;
		int type;
		string type_str;

		/**
			Parse School object from Json Value object

			@param json Json Value Object
			@return School object
		*/
		static School parse(Json::Value json);
	};

	/**
		A User class describes a user.
	*/
	class User: public Model{
		public:
			string first_name;
			string last_name;
			bool online;
			bool online_mobile;
			string photo_50;
			string photo_100;
			string photo_200;

			/**
				Parse user from Json Value Object

				@param json Json Value Object
				@return User object
			*/
			static User parse(Json::Value json);
		private:

	};

	class UserFull: public User{
		private:

			/**
				A Sex class describes a sex field
			*/
			class Sex{
				public:
					const int MALE = 2;
					const int FEMALE = 1;
			};

			/**
				A Contacts class describes a contacts field
			*/
			class Contacts: public Model{
				public:
					string mobile_phone;
					string home_phone;

					static UserFull::Contacts parse(Json::Value);
			};

			/**
				A Occupation class describes a information about the current occupation user
			*/
			class Occupation: public Model{
			public:
				const string TYPE_WORK = "work";
				const string TYPE_SCHOOL = "school";
				const string TYPE_UNIVERSITY = "university";

				string type;
				int id;
				string name;
			};

			class Relation{
			public:
				const int SINGLE = 1;
		        const int RELATIONSHIP = 2;
		        const int ENGAGED = 3;
		        const int MARRIED = 4;
		        const int COMPLICATED = 5;
	        	const int SEARCHING = 6;
		        const int IN_LOVE = 7;		
			};

			class Attitude{
			public:
				const int VERY_NEGATIVE = 1;
				const int NEGATIVE = 2;
				const int COMPROMISABLE = 3;
				const int NEUTRAL = 4;
				const int POSITIVE = 5;
			};

			class Political{
			public:
				const int COMMUNNIST = 1;
				const int SOCIALIST = 2;
				const int CENTRIST = 3;
				const int LIBERAL = 4;
				const int CONSERVATIVE = 5;
				const int MONARCHIST = 6;
				const int ULTRACONSERVATIVE = 7;
				const int LIBERTARIAN = 8;
				const int APATHETIC = 9;
			};

			class LifeMain{
				const int FAMILY_AND_CHILDREN = 1;
				const int CAREER_AND_MONEY = 2;
				const int ENTERTAINMENT_AND_LEISURE = 3;
				const int SCIENCE_AND_RESEARCH = 4;
				const int IMPROOVING_THE_WORLD = 5;
				const int PERSONAL_DEVELOPMENT = 6;
				const int BEAUTY_AND_ART = 7;
				const int FAME_AND_INFLUENCE = 8;
			};

			class PeopleMain{
				const int INTELLECT_AND_CREATIVITY = 1;
				const int KINDNESS_AND_HONESTLY = 2;
				const int HEALTH_AND_BEAUTY = 3;
				const int WEALTH_AND_POWER = 4;
				const int COURAGE_AND_PERSISTENCE = 5;
				const int HUMOR_AND_LOVE_FOR_LIFE = 6;
			};

			class RelativeType{
				const string PARTNER = "partner";
				const string GRANDCHILD = "grandchild";
				const string GRANDPARENT = "grandparent";
				const string CHILD = "child";
				const string SUBLING = "sibling";
				const string PARENT = "parent";
			};
		public:
			/**
				A Seen class describes a user seen (Time & Platform)
			*/
			class Seen: public Model{
			public:
				static const int PLATFORM_MOBILE = 1;
				static const int PLATFORM_IPHONE = 2;
				static const int PLATFORM_IPAD = 3;
				static const int PLATFORM_ANDROID = 4;
				static const int PLATFORM_WPHONE = 5;
				static const int PLATFORM_WINDOWS = 6;
				static const int PLATFORM_WEB = 7;

				long long int time;
				int platform;

				static string getPlatformName(int platform);
				static UserFull::Seen parse(Json::Value);
			};


			string photo_id;
			bool verified;
			bool blacklisted;
			int sex;
			string bdate;
			City city;
			Country country;
			string home_town;
			string list;
			string domain;
			bool has_mobile;
			UserFull::Contacts contacts;
			string site;
			Education education;
			vector<University> universities;
			vector<School> schools;
			string status;
			UserFull::Seen last_seen;
			int followers_count;
			int common_count;
			map<string, int> counters;
			UserFull::Occupation occupation;
			string nickname;
			//relaives
			int relation;
			//personal
			//connections
			//exports
			bool wall_comments;
			string activities;
			string interests;
			string music;
			string movies;
			string tv;
			string books;
			string games;
			string about;
			string quotes;
			bool can_post;
			bool can_see_all_posts;
			bool can_see_audio;
			bool can_write_private_message;
			bool can_send_friend_request;
			bool is_favorite;
			int timezone;
			string screen_name;
			string maiden_name;
			//crop_photo
			bool is_friend;
			int friend_status;
			/**
				Parse user from Json Value Object

				@param json Json Value Object
				@return UserFull object
			*/
			static UserFull parse(Json::Value);
	};

	class Utils{
		public:
			static string data2str(map<string, string>);
			static string urlencode(const string &c);
			static string char2hex(char);
			static int CURL_WRITER(char *data, size_t size, size_t nmemb, string *buffer);
	};

	class Parameters: public map<string, string>{
	public:
		//Commons
	    static const string USER_ID;
	    static const string USER_IDS;
	    static const string FIELDS;
	    static const string SORT;
	    static const string OFFSET;
	    static const string COUNT;
	    static const string OWNER_ID;

	    //auth
	    static const string VERSION;
	    static const string HTTPS;
	    static const string LANG;
	    static const string ACCESS_TOKEN;
	    static const string SIG;

	    //get users
	    static const string NAME_CASE;

	    //Get subscriptions
	    static const string EXTENDED;

	    //Search
	    static const string Q;
	    static const string CITY;
	    static const string COUNTRY;
	    static const string HOMETOWN;
	    static const string UNIVERSITY_COUNTRY;
	    static const string UNIVERSITY;
	    static const string UNIVERSITY_YEAR;
	    static const string SEX;
	    static const string STATUS;
	    static const string AGE_FROM;
	    static const string AGE_TO;
	    static const string BIRTH_DAY;
	    static const string BIRTH_MONTH;
	    static const string BIRTH_YEAR;
	    static const string ONLINE;
	    static const string HAS_PHOTO;
	    static const string SCHOOL_COUNTRY;
	    static const string SCHOOL_CITY;
	    static const string SCHOOL;
	    static const string SCHOOL_YEAR;
	    static const string RELIGION;
	    static const string INTERESTS;
	    static const string COMPANY;
	    static const string POSITION;
	    static const string GROUP_ID;

	    static const string FRIENDS_ONLY;
	    static const string FROM_GROUP;
	    static const string MESSAGE;
	    static const string ATTACHMENTS;
	    static const string SERVICES;
	    static const string SIGNED;
	    static const string PUBLISH_DATE;
	    static const string LAT;
	    static const string LONG;
	    static const string PLACE_ID;
	    static const string POST_ID;

	    //Errors
	    static const string ERROR_CODE;
	    static const string ERROR_MSG;
	    static const string REQUEST_PARAMS;

	    //Captcha
	    static const string CAPTCHA_IMG;
	    static const string CAPTCHA_SID;
	    static const string CAPTCHA_KEY;
	    static const string REDIRECT_URI;

	    //Photos
	    static const string PHOTO;
	    static const string PHOTOS;
	    static const string ALBUM_ID;
	    static const string PHOTO_IDS;
	    static const string PHOTO_SIZES;
	    static const string REV;
	    static const string FEED_TYPE;
	    static const string FEED;

	    Parameters();
	    //Parameters(map<string, string> data);
	    string join(string...);
	};
	
	class UsersList: public Model{
	public:
		vector<UserFull> list;
		UsersList(vector<VK::UserFull> users);
		UsersList(Json::Value json);
		
		vector<UserFull> toVector();
		
		static vector<UserFull> parse(Json::Value json);
	};
	
	class  Response{
	public:
		
	};
	
	/**
		@brief API class
	*/
	class API{
		public:
			static string api_url;
			string access_token;
			int user_id;
			string version;
			string lang;
			string https;

			/**
				API constructor

				@param version Api version
				@param lang Api language
				@param https Api requests via https
				@param access_token Access token for requests
			*/
			API(string version, string lang, bool https, string access_token);

			/**
				HTTP Post request

				@param url request url
				@param data data string
				@return json string
			*/
			static string post(string url, string data);

			/**
				HTTP Post request

				@param url method name
				@param data map of data
				@return json Json Value Object
			*/
			Json::Value call(string method, map<string, string> params);

			UsersList usersGet(map<string, string> params);
			vector<UserFull> usersSearch(map<string, string> params);
			bool usersIsAppUser(map<string, string> params);
			vector<UserFull> usersGetSubscriptions(map<string, string> params);
			vector<UserFull> usersGetFollowers(map<string, string> params);
			vector<UserFull> usersReport(int user_id, string type, map<string, string> params);
			vector<UserFull> usersGetNearby(double latitude, double longitude, map<string, string> params);
		
		private:

	};
}
#endif