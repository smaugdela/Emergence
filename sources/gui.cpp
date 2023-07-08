#include "emergence.hpp"

void gui(std::vector<particle_type *> &types, std::vector<std::vector<float>> &interactions, std::vector<std::vector<Particle *>> &particles, sf::RenderWindow &window)
{
	bool showImGuiWindow = true;

	ImGui::SetNextWindowPos(ImVec2(5, 5), ImGuiCond_Always);
	ImGui::Begin("Settings", &showImGuiWindow, ImGuiWindowFlags_NoMove);
	if (showImGuiWindow == false)
		window.close();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
	ImGui::PushItemWidth(300.f);
	ImGui::Text("That's where you play God.");
	if (ImGui::CollapsingHeader("Hyper-Parameters"))
	{
		ImGui::Text("You can change the hyper-parameters of the simulation here. Be careful, somechanges may lead to unexpected or extreme results.");

		bool paused = my_settings.get_pause();
		ImGui::Checkbox("Pause", &paused);
		my_settings.set_pause(paused);
		ImGui::Text("FPS: %d", (int)ImGui::GetIO().Framerate);
		ImGui::NewLine();
		bool new_doppler = my_settings.get_doppler_effect();
		ImGui::Checkbox("Doppler Effect", &new_doppler);
		my_settings.set_doppler_effect(new_doppler);
		ImGui::SameLine();
		float new_doppler_factor = my_settings.get_doppler_factor();
		ImGui::SliderFloat("Doppler Factor", &new_doppler_factor, 1.0f, 1000.0f);
		my_settings.set_doppler_factor(new_doppler_factor);
		bool new_3d = my_settings.get_3d();
		ImGui::Checkbox("3D", &new_3d);
		my_settings.set_3d(new_3d);
		float new_radius = my_settings.get_particle_size();
		ImGui::SliderFloat("Particle Radius", &new_radius, 1.0f, 10.0f);
		my_settings.set_particle_size(new_radius);
		float force_factor = my_settings.get_force_factor();
		if (my_settings.get_3d() == false)
			ImGui::SliderFloat("Force Factor", &force_factor, 0.0f, 1000.0f);
		else
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

		// Output file name
		static char filename[128] = "";
		ImGui::InputText("##filename", filename, IM_ARRAYSIZE(filename));
		ImGui::SameLine();

		// Save to file button
		if (ImGui::Button("Save To File"))
		{
			if (filename[0] == '\0')
				my_settings.save_to_json("default.json", types, interactions);
			else
			{
				std::string filename_str = filename;
				if (filename_str.find(".json") == std::string::npos)
					filename_str += ".json";
				my_settings.save_to_json(filename_str, types, interactions);
			}
		}
		ImGui::NewLine();
		// List all json files in the current directory
		ImGui::Text("Load From File");
		ImGui::SameLine();
		ImGui::PushItemWidth(200.f);
		std::vector<std::string> files;
		for (const auto &entry : std::filesystem::directory_iterator("."))
		{
			if (entry.path().extension() == ".json")
			{
				std::string filename = entry.path().filename().string();
				files.push_back(filename);
			}
		}

		// Convert the filenames vector to a C-style array of const char*
		std::vector<const char *> cFiles;
		cFiles.reserve(files.size());
		for (const auto &file : files)
		{
			cFiles.push_back(file.c_str());
		}

		// Drop down menu to select the JSON file to load
		static int selected_json = 0;
		ImGui::Combo("##json", &selected_json, cFiles.data(), static_cast<int>(cFiles.size()));
		ImGui::SameLine();
		if (ImGui::Button("Load"))
		{
			// Replace current process with a new one using execve
			extern char **environ;
			std::string command = "./emergence";
			char *args[] = {const_cast<char *>("emergence"), const_cast<char *>(cFiles[selected_json]), nullptr};
			free(particles, types);
			execve(command.c_str(), args, environ);
			exit(EXIT_FAILURE);
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

			// Use ColorEdit3 or ColorEdit4 for color picking
			if (ImGui::ColorEdit3(("Color" + std::to_string(item->id)).c_str(), reinterpret_cast<float *>(&color), ImGuiColorEditFlags_NoInputs))
			{
				// Update the color when it's changed in the color picker
				item->color.r = static_cast<uint8_t>(color.x * 255);
				item->color.g = static_cast<uint8_t>(color.y * 255);
				item->color.b = static_cast<uint8_t>(color.z * 255);
			}
			ImGui::SameLine();
			ImGui::Text("id: %li", item->id);
			ImGui::SameLine();
			int amount = int(item->amount);
			ImGui::SliderInt((std::string("Amount ") + std::to_string(item->id)).c_str(), &amount, 0, 1000, "%d");
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

		bool symmetric = my_settings.get_energy_conservation();
		ImGui::Checkbox("Symmetric", &symmetric);
		if (symmetric)
		{
			for (size_t i = 0; i < interactions.size(); i++)
			{
				for (size_t j = 0; j < interactions.size(); j++)
				{
					if (i != j)
					{
						interactions[j][i] = interactions[i][j];
					}
				}
			}
		}
		my_settings.set_energy_conservation(symmetric);

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

	ImGui::PopItemWidth();
	ImGui::PopStyleVar();
	ImGui::End();
}
