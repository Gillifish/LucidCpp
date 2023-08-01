#include "App.h"

App::App(float x, float y, std::string title, float fr, DataManager &db) : m_width(x),
                                                                           m_height(y),
                                                                           m_db(db)

{
    m_window.create(sf::VideoMode(m_width, m_height), title);
    m_window.setFramerateLimit(fr);
    ImGui::SFML::Init(m_window);
}

void App::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // Careful not to input this twice
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
        {
            quit();
        }

        if (event.type == sf::Event::Resized)
        {
            m_width = event.size.width;
            m_height = event.size.height;
        }
    }
}

void App::sImGui()
{
    ImGui::SetNextWindowSize(ImVec2(m_width, m_height)); // Set to zero to fit the entire window
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    mainWindow();

    if (m_showAddWindow)
    {
        addWindow();
    }

    if (m_showRemoveWindow)
    {
        removeWindow();
    }
}

void App::addWindow()
{
    ImGui::SetNextWindowSize(ImVec2(300, 150));

    ImGui::Begin("Add", nullptr, m_addWindowFlags);

    static char accName[16] = "";
    static char username[16] = "";
    static char password[16] = "";

    ImGui::InputText("Account Name", accName, IM_ARRAYSIZE(accName));
    ImGui::InputText("Username", username, IM_ARRAYSIZE(username));
    ImGui::InputText("Password", password, IM_ARRAYSIZE(password));

    if (ImGui::Button("Add"))
    {
        Account acc;
        acc.tag = accName;
        acc.username = username;
        acc.password = password;

        m_db.add(acc);

        accName[0] = '\0';
        username[0] = '\0';
        password[0] = '\0';
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel"))
    {
        accName[0] = '\0';
        username[0] = '\0';
        password[0] = '\0';

        m_showAddWindow = false;
    }

    ImGui::End();
}

void App::removeWindow()
{
    ImGui::SetNextWindowSize(ImVec2(300, 150));

    ImGui::Begin("Remove", nullptr, m_addWindowFlags);

    static char accName[16] = "";
    static char username[16] = "";
    static char password[16] = "";

    ImGui::InputText("Account Name", accName, IM_ARRAYSIZE(accName));
    ImGui::InputText("Username", username, IM_ARRAYSIZE(username));
    ImGui::InputText("Password", password, IM_ARRAYSIZE(password));

    if (ImGui::Button("Remove"))
    {
        Account acc;
        acc.tag = accName;
        acc.username = username;
        acc.password = password;

        m_db.remove(acc);

        accName[0] = '\0';
        username[0] = '\0';
        password[0] = '\0';
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel"))
    {
        accName[0] = '\0';
        username[0] = '\0';
        password[0] = '\0';

        m_showRemoveWindow = false;
    }

    ImGui::End();
}

void App::mainWindow()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {

            if (ImGui::MenuItem("Add"))
            {
                m_showAddWindow = true;
            }
            else if (ImGui::MenuItem("Remove"))
            {
                m_showRemoveWindow = true;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Search"))
        {
            static char searchBuff[128] = "";
            ImGui::InputText("", searchBuff, IM_ARRAYSIZE(searchBuff));

            if (ImGui::MenuItem("Search"))
            {
                searchBuff[0] = '\0';
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    ImGui::Separator();

    ImGui::SetNextWindowSize(ImVec2(m_width, m_height - 19));
    ImGui::SetNextWindowPos(ImVec2(0, 19));

    ImGui::Begin("MainWindow", nullptr, m_mainWindowFlags);

    displayData();

    ImGui::End();
}

void App::displayData()
{
    if (ImGui::BeginTable("Data", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupColumn("Account Name");
        ImGui::TableSetupColumn("User");
        ImGui::TableSetupColumn("Password");
        ImGui::TableHeadersRow();

        for (auto acc : m_db.data())
        {
            ImGui::TableNextColumn();
            ImGui::Text("%s", acc.tag.c_str());

            ImGui::TableNextColumn();
            ImGui::Text("%s", acc.username.c_str());

            ImGui::TableNextColumn();
            ImGui::Text("%s", acc.password.c_str());
        }

        ImGui::EndTable();
    }
}

void App::update()
{
    sUserInput();

    // MUST BE AFTER INPUT IS PROCESSED
    ImGui::SFML::Update(m_window, deltaClock.restart());
    sImGui();
}

void App::run()
{
    while (isRunning())
    {
        m_window.clear(m_background);
        update();
        ImGui::SFML::Render(m_window);
        m_window.display();
    }
}

void App::quit()
{
    m_running = false;
}

sf::RenderWindow &App::window()
{
    return m_window;
}

bool App::isRunning()
{
    return m_running & m_window.isOpen();
}

App::~App()
{
    ImGui::SFML::Shutdown();
}