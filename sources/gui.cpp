#include "emergence.hpp"

void gui(std::vector<particle_type *> &types, std::vector<std::vector<float>> &interactions, std::vector<std::vector<Particle *>> &particles, sf::RenderWindow &window)
{
	bool showImGuiWindow = true;

	ImGui::Begin("Settings", &showImGuiWindow, ImGuiWindowFlags_NoMove);
	if (showImGuiWindow == false)
		window.close();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
	ImGui::Text("That's where you play God.");
	if (ImGui::CollapsingHeader("Hyper-Parameters"))
	{
		ImGui::Text("You can change the hyper-parameters of the simulation here. Be careful, somechanges may lead to unexpected or extreme results.");
		ImGui::Text("FPS: %d", (int)ImGui::GetIO().Framerate);
		bool new_3d = my_settings.get_3d();
		ImGui::Checkbox("3D", &new_3d);
		my_settings.set_3d(new_3d);
		float new_radius = my_settings.get_particle_size();
		ImGui::SliderFloat("Particle Radius", &new_radius, 1.0f, 10.0f);
		my_settings.set_particle_size(new_radius);
		float force_factor = my_settings.get_force_factor();
		ImGui::SliderFloat("Force Factor", &force_factor, 0.0f, 5000.0f);
		my_settings.set_force_factor(force_factor);
		float friction_coefficient = my_settings.get_friction_coefficient();
		ImGui::SliderFloat("Friction Coefficient", &friction_coefficient, 0.0f, 1.0f);
		my_settings.set_friction_coefficient(friction_coefficient);
		float boundary_limit = my_settings.get_boundary_limit();
		ImGui::SliderFloat("Boundary Limit", &boundary_limit, 0.0f, 1.0f);
		my_settings.set_boundary_limit(boundary_limit);
		float max_range = std::sqrt(my_settings.get_max_range());
		ImGui::SliderFloat("Max Range", &max_range, 0.0f, 1000.0f);
		my_settings.set_max_range(max_range);
		float new_temperature = my_settings.get_temperature();
		ImGui::SliderFloat("Temperature", &new_temperature, 0.0f, 1.0f);
		my_settings.set_temperature(new_temperature);
		ImGui::NewLine();
		if (ImGui::Button("Save To File"))
		{
			my_settings.save_to_json("output.json", types, interactions);
		}
		ImGui::NewLine();
	}
	if (ImGui::CollapsingHeader("Particle types"))
	{
		ImGui::Text("You can add, delete and modify the particles amount for each types here.");
		// Print the list of items with colored blocks
		for (auto &item : types)
		{
			// Convert the type color to ImVec4
			ImVec4 color = ImVec4(item->color.r / 255.0f, item->color.g / 255.0f, item->color.b / 255.0f, 255.0f);

			ImGui::ColorButton(("Color" + std::to_string(item->id)).c_str(), color);
			ImGui::SameLine();
			ImGui::Text("id: %li", item->id);
			ImGui::SameLine();
			int amount = int(item->amount);
			ImGui::SliderInt((std::string("Amount ") + std::to_string(item->id)).c_str(), &amount, 0, 1000);
			item->amount = amount;
			ImGui::SameLine();
			size_t indexToDelete = 0;
			bool deletion = false;
			if (types.size() > 1)
			{
				if (ImGui::Button((std::string("Delete ") + std::to_string(item->id)).c_str()))
				{
					indexToDelete = item->id;
					deletion = true;
				}
			}
			// Delete the selected items outside the loop
			if (deletion)
			{
				// Delete the particles of the deleted type
				for (auto &particle : particles[indexToDelete])
					delete particle;
				particles.erase(particles.begin() + indexToDelete);

				// Remove type from interactions
				for (auto &row : interactions)
					row.erase(row.begin() + indexToDelete);
				interactions.erase(interactions.begin() + indexToDelete);

				// Delete the type
				delete types[indexToDelete];
				types.erase(types.begin() + indexToDelete);

				// Replace correctly the type ids
				for (size_t current_id = 0; current_id < types.size(); current_id++)
				{
					if (types[current_id]->id != current_id)
						types[current_id]->id = current_id;
				}
			}
		}

		// Add a new type
		ImGui::NewLine();
		if (types.size() < 10 && ImGui::Button("Add a new type"))
		{
			particle_type *new_type = new particle_type();
			new_type->id = types.size();
			new_type->color = sf::Color(255, 255, 255);
			new_type->amount = 1;
			types.push_back(new_type);

			// Update interactions: add a row and column of 0.0f
			for (size_t i = 0; i < interactions.size(); i++)
			{
				interactions[i].push_back(0.0f);
			}
			std::vector<float> new_interactions(types.size(), 0.0f);
			interactions.push_back(new_interactions);

			// Update particles: add a vector of particles
			std::vector<Particle *> new_particles;
			particles.push_back(new_particles);
		}
	}

	if (ImGui::CollapsingHeader("Interaction Matrix"))
	{
		ImGui::Text("You can modify the interaction matrix here. Each <ij> coefficient represent how much particles of type <i> are attracted (or repelled if negative) to particles of type <j>.");
		// First print the type families
		for (const auto &item : types)
		{
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 70);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
			ImGui::Text("%li", item->id);
			ImGui::SameLine();
			ImGui::ColorButton(" ", ImVec4(item->color.r / 255.0f, item->color.g / 255.0f, item->color.b / 255.0f, 255.0f), ImGuiColorEditFlags_NoPicker);
			ImGui::SameLine();
			ImGui::PopStyleVar();
		}
		ImGui::NewLine();

		// Display the matrix as a selectable grid
		size_t j = 0;
		for (auto &row : interactions)
		{
			// Print the type family for each line
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
			ImGui::Text("%li", types[j]->id);
			ImGui::SameLine();
			ImGui::ColorButton(" ", ImVec4(types[j]->color.r / 255.0f, types[j]->color.g / 255.0f, types[j]->color.b / 255.0f, 255.0f), ImGuiColorEditFlags_NoPicker);
			ImGui::SameLine();
			ImGui::PopStyleVar();

			size_t i = 0;
			for (auto &item : row)
			{
				std::string index = std::to_string(i) + std::to_string(j);
				ImGui::PushItemWidth(100);
				ImGui::SliderFloat(index.c_str(), &item, -1.0f, 1.0f, "%.2f");
				ImGui::PopItemWidth();
				ImGui::SameLine();
				++i;
			}
			ImGui::NewLine();
			++j;
		}
	}

	ImGui::PopStyleVar();
	ImGui::End();
}
