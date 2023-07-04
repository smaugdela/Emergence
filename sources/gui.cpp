#include "emergence.hpp"

void gui(std::vector<particle_type> &types, std::vector<std::vector<float>> &interactions, sf::RenderWindow &window)
{

	(void)interactions;

	bool showImGuiWindow = true;

	ImGui::Begin("Settings", &showImGuiWindow, ImGuiWindowFlags_NoMove);
	if (showImGuiWindow == false)
		window.close();

	ImGui::Text("That's where you play God.");

	if (ImGui::CollapsingHeader("Particle types"))
	{
		// Print the list of items with colored blocks
		for (const auto &item : types)
		{
			// Convert the type color to ImVec4
			ImVec4 color = ImVec4(item.color.r / 255.0f, item.color.g / 255.0f, item.color.b / 255.0f, 255.0f);

			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
			ImGui::ColorButton(std::to_string(item.id).c_str(), color, ImGuiColorEditFlags_NoPicker);
			ImGui::SameLine();
			ImGui::Text("id: %li", item.id);
			ImGui::SameLine();
			ImGui::Text("amount: %li", item.amount);
			ImGui::PopStyleVar();
		}
	}

	if (ImGui::CollapsingHeader("Interaction Matrix"))
	{

		// First print the type families

		for (const auto &item : types)
		{
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 80);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
			ImGui::Text("%li", item.id);
			ImGui::SameLine();
			ImGui::ColorButton(std::to_string(item.id).c_str(), ImVec4(item.color.r / 255.0f, item.color.g / 255.0f, item.color.b / 255.0f, 255.0f), ImGuiColorEditFlags_NoPicker);
			ImGui::SameLine();
			ImGui::PopStyleVar();
		}
		ImGui::NewLine();

		// Display the matrix as a selectable grid
		size_t i = 0;
		size_t j = 0;
		for (auto &row : interactions)
		{
			// Print the type family for each line
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
			ImGui::Text("%li", types[j].id);
			ImGui::SameLine();
			ImGui::ColorButton(std::to_string(types[j].id).c_str(), ImVec4(types[j].color.r / 255.0f, types[j].color.g / 255.0f, types[j].color.b / 255.0f, 255.0f), ImGuiColorEditFlags_NoPicker);
			ImGui::SameLine();
			ImGui::PopStyleVar();

			for (auto &item : row)
			{
				// Convert the float item to string
				// std::string item_str;
				// if (item >= 0.f)
				// 	item_str = std::to_string(item).substr(0, 4);
				// else
				// 	item_str = std::to_string(item).substr(0, 5);

				ImGui::PushItemWidth(100);
				// ImGui::Button(item_str.c_str(), ImVec2(50, 50));
				// ImGui::SliderFloat(" ", &item, -1.0f, 1.0f, "%.2f");
				ImGui::SliderFloat(std::to_string(i).c_str(), &item, -1.0f, 1.0f, "%.2f");
				ImGui::PopItemWidth();
				ImGui::SameLine();
				++i;
			}
			ImGui::NewLine();
			++j;
		}

		// ImGui::PopStyleVar(3); // Pop the style variables
	}

	ImGui::End();
}
