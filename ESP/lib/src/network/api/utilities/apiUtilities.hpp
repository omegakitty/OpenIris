#ifndef APIUTILITIES_HPP
#define APIUTILITIES_HPP

#include <unordered_map>
#include <string>

#define WEBSERVER_H

/* #define XHTTP_GET 0b00000001;
#define XHTTP_POST 0b00000010;
#define XHTTP_DELETE 0b00000100;
#define XHTTP_PUT 0b00001000;
#define XHTTP_PATCH 0b00010000;
#define XHTTP_HEAD 0b00100000;
#define XHTTP_OPTIONS 0b01000000;
#define XHTTP_ANY 0b01111111; */

#define HTTP_ANY 0b01111111
#define HTTP_GET 0b00000001

#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "mbedtls/md.h"
#include "data/utilities/network_utilities.hpp"
#include "data/StateManager/StateManager.hpp"
#include "io/camera/cameraHandler.hpp"

class API_Utilities
{
public:
	API_Utilities(int CONTROL_PORT,
				  WiFiHandler *network,
				  CameraHandler *camera,
				  StateManager<WiFiState_e> *stateManager,
				  std::string api_url);
	virtual ~API_Utilities();

protected:
	void notFound(AsyncWebServerRequest *request) const;
	/* String readFile(fs::FS &fs, std::string path);
	void writeFile(fs::FS &fs, std::string path, std::string message); */
	std::string shaEncoder(std::string data);
	std::unordered_map<int, std::string> _networkMethodsMap = {
		{0, "NULL"},
		{0b00000001, "GET"},
		{0b00000010, "POST"},
		{0b00001000, "PUT"},
		{0b00000100, "DELETE"},
		{0b00010000, "PATCH"},
		{0b01000000, "OPTIONS"},
	};

	enum RequestMethods
	{
		NULL_METHOD,
		GET,
		POST,
		PUT,
		DELETE,
		PATCH,
		OPTIONS,
	};

	std::unordered_map<int, RequestMethods> _networkMethodsMap_enum = {
		{0, NULL_METHOD},
		{0b00000001, GET},
		{0b00000010, POST},
		{0b00001000, PUT},
		{0b00000100, DELETE},
		{0b00010000, PATCH},
		{0b01000000, OPTIONS},
	};

protected:
	AsyncWebServer *server;
	WiFiHandler *network;
	CameraHandler *camera;
	StateManager<WiFiState_e> *stateManager;
	typedef std::unordered_map<std::string, WebRequestMethodComposite> networkMethodsMap_t;

protected:
	std::string api_url;

	static bool ssid_write;
	static bool pass_write;
	static bool channel_write;

	static const char *MIMETYPE_HTML;
	/* static const char *MIMETYPE_CSS; */
	/* static const char *MIMETYPE_JS; */
	/* static const char *MIMETYPE_PNG; */
	/* static const char *MIMETYPE_JPG; */
	/* static const char *MIMETYPE_ICO; */
	static const char *MIMETYPE_JSON;
};

#endif // APIUTILITIES_HPP