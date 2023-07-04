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
			// ImGui::SliderInt("amount", &item.amount, 0, 100);
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
			ImGui::ColorButton(" ", ImVec4(item.color.r / 255.0f, item.color.g / 255.0f, item.color.b / 255.0f, 255.0f), ImGuiColorEditFlags_NoPicker);
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
			ImGui::ColorButton(" ", ImVec4(types[j].color.r / 255.0f, types[j].color.g / 255.0f, types[j].color.b / 255.0f, 255.0f), ImGuiColorEditFlags_NoPicker);
			ImGui::SameLine();
			ImGui::PopStyleVar();

			for (auto &item : row)
			{
				ImGui::PushItemWidth(100);
				ImGui::SliderFloat(std::to_string(i).c_str(), &item, -1.0f, 1.0f, "%.2f");
				ImGui::PopItemWidth();
				ImGui::SameLine();
				++i;
			}
			ImGui::NewLine();
			++j;
		}
	}

	ImGui::End();
}
