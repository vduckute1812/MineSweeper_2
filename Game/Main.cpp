#include <stdio.h>
#if defined(_WIN32) || defined(WIN32)
#include "glew/glew.h"
#include "glfw/glfw3.h"
#endif
#include "Define.h"
#include "MainState.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "DebugDraw.h"
#include <string> 

#ifdef __unix__ 
#include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif


namespace
{
	GLFWwindow* mainWindow = nullptr;

	int32 testIndex = 0;
	int32 testSelection = 0;
	int32 testCount = 0;
	bool rightMouseDown;
	b2Vec2 lastp;
}

#ifdef CHECK_MODE_FROM_FILE
void GetGameModeFromConfigFile()
{
	int GameModeLoadFromConfigFile = -1;
	string STRING;
	ifstream infile;
	infile.open("config.txt");
	if (infile.is_open())
	{
		getline(infile, STRING); // Saves the line in STRING.
	}
	infile.close();
	char output[100];
	strcpy(output, STRING.c_str());	
	if (strcmp(output, "Gamemode=NO_GUI") == 0)
	{
		GameModeLoadFromConfigFile =  3;
	}
	else if (strcmp(output, "Gamemode=Extra") == 0)
	{		
		GameModeLoadFromConfigFile =  1;
	}
	else if (strcmp(output, "Gamemode=Pen") == 0)
	{
		GameModeLoadFromConfigFile =  2;
	}
	else if (strcmp(output, "Gamemode=Short") == 0)
	{
		GameModeLoadFromConfigFile = 4;
		m_MainState->GetInstance()->SetGameShortMode();
	}
	else
	{
		GameModeLoadFromConfigFile = 0;
	}
	
	m_MainState->GetInstance()->SetGameModeFromFileConfig(GameModeLoadFromConfigFile);
}
#endif //CHECK_MODE_FROM_FILE

#ifdef DEBUG_SERVER
static void sCreateUI( GLFWwindow* window )
{
	// Init UI
	const char* fontPath = "Data/DroidSans.ttf";
	ImGui::GetIO().Fonts->AddFontFromFileTTF( fontPath, 15.f );

	if( ImGui_ImplGlfwGL3_Init( window, false ) == false )
	{
		fprintf( stderr, "Could not init GUI renderer.\n" );
		assert( false );
		return;
	}

	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameRounding = style.GrabRounding = style.ScrollbarRounding = 2.0f;
	style.FramePadding = ImVec2( 40, 2 );
	style.DisplayWindowPadding = ImVec2( 0, 0 );
	style.DisplaySafeAreaPadding = ImVec2( 0, 0 );
}
#endif // DEBUG_SERVER


void displayMe( void )
{
	//glClear( GL_COLOR_BUFFER_BIT );
	//glBegin( GL_POLYGON );
	//glVertex2f( 0.0, 0.0 );                    // bottom left
	//glVertex2f( 0.5, 0.0 );                    // bottom right
	//glVertex2f( 0.5, 0.5 );                    // top right
	//glVertex2f( 0.0, 0.5 );                    // top left
	//glEnd();
	//glFlush();
}
#ifdef DEBUG_SERVER
void glfwErrorCallback( int error, const char *description )
{
	fprintf( stderr, "GLFW error occured. Code: %d. Description: %s\n", error, description );
}

static void sSimulate()
{
	glEnable( GL_DEPTH_TEST );

	glDisable( GL_DEPTH_TEST );

	if( testSelection != testIndex )
	{
		g_camera.m_zoom = 1.0f;
		g_camera.m_center.Set( 0.0f, 20.0f );
	}
}
#endif // DEBUG_SERVER
int main(int argc, char* argv[])
{
#ifdef CHECK_MODE_FROM_FILE
	GetGameModeFromConfigFile();
#endif

#ifdef DEBUG_SERVER

#if defined(_WIN32)
	// Enable memory-leak reports
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
#endif
	glfwSetErrorCallback(glfwErrorCallback);

	g_camera.m_width  = MAP_SIZE / DRAW_SCALE + 2 * OFFSET_X;
	g_camera.m_height = MAP_SIZE / DRAW_SCALE + 2 * OFFSET_Y;

	if (glfwInit() == 0)
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	char title[64];
	sprintf(title, "GameServer");

	mainWindow = glfwCreateWindow(g_camera.m_width, g_camera.m_height, title, nullptr, nullptr);
	if (mainWindow == nullptr)
	{
		fprintf(stderr, "Failed to open GLFW mainWindow.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(mainWindow);
#if defined(__APPLE__) == FALSE
	//glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
#endif
	g_debugDraw.Create();
	sCreateUI(mainWindow);
	double time1 = glfwGetTime();
#endif // DEBUG_SERVER
	double frameTime = 0.0;
	int gameTurn = 0;
	//init();
	//m_MainState->GetInstance()->ConfigBot( argv[1], argv[2], atoi( argv[3] ), atoi( argv[4] ), argv[5] );
	string pathSave = "TheGameServer\\";
	if (argv[1])
		pathSave = argv[1];
		cerr << "Argu: " << pathSave;
	bool isExtraTime = true;
	//if( argv[2] && atoi( argv[2] ) == 1 )
	//{
		isExtraTime = false;
		cerr << "Extra: " << isExtraTime;
	//}

#ifdef DEBUG_SERVER
	glClearColor( 0.3f, 0.3f, 0.3f, 1.f );
#endif // DEBUG_SERVER
	/*
	while( !glfwWindowShouldClose( mainWindow ) )
	{
		glfwGetWindowSize( mainWindow, &g_camera.m_width, &g_camera.m_height );
		int bufferWidth, bufferHeight;
		glfwGetFramebufferSize( mainWindow, &bufferWidth, &bufferHeight );
		glViewport( 0, 0, bufferWidth, bufferHeight );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::SetNextWindowPos( ImVec2( 0, 0 ) );
		ImGui::SetNextWindowSize( ImVec2( (float)g_camera.m_width, (float)g_camera.m_height ) );
		ImGui::Begin( "Overlay", NULL, ImVec2( 0, 0 ), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar );
		ImGui::SetCursorPos( ImVec2( 5, (float)g_camera.m_height - 20 ) );
		ImGui::Text( "%.1f ms", 1000.0 * frameTime );
		ImGui::End();
		glEnable( GL_DEPTH_TEST );
		g_debugDraw.Flush();
		//g_camera.m_zoom = 2.0f;
		//g_camera.m_center.Set( 0.0f, 20.0f );
		b2Vec2 center = { 400.0f, 240.0f };
		b2Vec2 centerW1 = g_camera.ConvertScreenToWorld( center );
		//b2Vec2 centerW = g_camera.ConvertScreenToWorld( center );
		//printf("\nAAAAAAAAA %f %f", centerW.x,centerW.y);
		//b2Vec2 centerW1 = g_camera.ConvertWorldToScreen( center );
		//printf( "\nAAAAAAAAAW %f %f", centerW1.x, centerW1.y );
		float32 radius = 2.0f;
		b2Color color( 0.95f, 0.95f, 0.6f );
		g_debugDraw.DrawCircle( centerW1, radius, color );
		// Measure speed
		
		double time2 = glfwGetTime();
		double alpha = 0.9f;
		frameTime = alpha * frameTime + ( 1.0 - alpha ) * ( time2 - time1 );
		time1 = time2;
		ImGui::Render();

		glfwSwapBuffers( mainWindow );
	}
	*/
	
	string filename = "";

#ifndef DEBUG_SERVER
	printf("END{'file':'%s', 'result':%d, 'score':'%s', 'lastTurn':%d}", filename.c_str(), result, m_MainState->GetInstance()->GetResultString().c_str(), gameTurn);
#else
	//printf("END{'result':%d, 'score':'%s', 'lastTurn':%d}", result, m_MainState->GetInstance()->GetResultString().c_str(), gameTurn);
#endif

	int m_time_sleep = 1;
#ifdef __unix__ 
	sleep(m_time_sleep);
#elif defined(_WIN32) || defined(WIN32)
	Sleep(m_time_sleep);
#endif
	return 0;
}
#ifdef DEBUG_SERVER
static void sResizeWindow( GLFWwindow*, int width, int height )
{
	g_camera.m_width = width / DRAW_SCALE;
	g_camera.m_height = height / DRAW_SCALE;
}
#endif // DEBUG_SERVER