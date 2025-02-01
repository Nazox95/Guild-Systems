quest guild_safebox begin
	state start begin
		-- Abrir Almac�n de la Guild
		when 60000.chat."Abrir almac�n de la guild" or 60001.chat."Abrir almac�n de la guild" or 60002.chat."Abrir almac�n de la guild" with pc.has_guild() and guild.has_guildstorage() begin --1591
			say("�Quieres abrir el almac�n de la guild?") --1593
			if select("S�", "No") == 2 then return end

			if guild.not_has_permission_for_open() then
				say("No tienes los permisos necesarios para[ENTER]abrir el almac�n de la guild.") --1592
				return
			end

			guild.open_guildstorage()
		end

		-- Comprar segunda p�gina del almac�n de la Guild
		when 60000.chat."Expandir almac�n de la guild" with pc.has_guild() and guild.has_guildstorage() begin --1589
			if guild.get_guildstorage_level() >= 3 then
				say("El almac�n de la guild ya ha alcanzado[ENTER]el tama�o m�ximo.") --1594
				return
			end

			say(string.format("Tama�o actual: %d (m�x. 3)", guild.get_guildstorage_level())) --1595
			say("Materiales necesarios para la pr�xima expansi�n:") --1596
			say_reward(string.format("%d Yang (cuenta de la guild)", 25000000)) --1597
			say_reward(string.format("Piedra base: %d", 40)) --1598
			say_reward(string.format("Tronco: %d", 35)) --1599
			say_reward(string.format("Contrachapado: %d", 30)) --1600
			say("")
			say("�Quieres expandir el almac�n de la guild?") --1601
			if select("S�", "No") == 2 then return end
			if pc.count_item(90010) >= 40 and pc.count_item(90012) >= 30 and pc.count_item(90011) >= 35 and pc.get_gold() >= 25000000 then
				guild.set_guildstorage_level(2)
				building.reconstruct(14072) -- Almac�n de la Guild LV. 2 (14072, 60001)
				pc.change_money(-25000000)
				pc.remove_item("90010", 40) -- Piedra base
				pc.remove_item("90011", 35) -- Tronco
				pc.remove_item("90012", 30) -- Contrachapado
				say(string.format("Tama�o actual: %d (m�x. 3)", 2)) --1595
			else
				if pc.get_gold() < 25000000 then
					say("La cuenta de la guild no tiene suficientes Yang.[ENTER]Por favor, agrega m�s Yang e int�ntalo de nuevo.") --1590
				elseif pc.count_item(90010) < 40 or pc.count_item(90012) < 30 or pc.count_item(90011) < 35 then
					say("No tienes los elementos necesarios.") --1590
				else
					say("Error10")
				end
			end
		end

		-- Comprar tercera p�gina del almac�n de la Guild
		when 60001.chat."Expandir almac�n de la guild" with pc.has_guild() and guild.has_guildstorage() begin --1589
			if guild.get_guildstorage_level() >= 3 then
				say("El almac�n de la guild ya ha alcanzado[ENTER]el tama�o m�ximo.") --1594
				return
			end

			say(string.format("Tama�o actual: %d (m�x. 3)", guild.get_guildstorage_level())) --1595
			say("Materiales necesarios para la pr�xima expansi�n:") --1596
			say_reward(string.format("%d Yang (cuenta de la guild)", 50000000)) --1597
			say_reward(string.format("Piedra base: %d", 50)) --1598
			say_reward(string.format("Tronco: %d", 45)) --1599
			say_reward(string.format("Contrachapado: %d", 40)) --1600
			say("")
			say("�Quieres expandir el almac�n de la guild?") --1601
			if select("S�", "No") == 2 then return end
			if pc.count_item(90010) >= 50 and pc.count_item(90012) >= 40 and pc.count_item(90011) >= 45 and pc.get_gold() >= 50000000 then
				guild.set_guildstorage_level(3)
				building.reconstruct(14073) -- Almac�n de la Guild LV. 3 (14073, 60002)
				pc.change_money(-50000000)
				pc.remove_item("90010", 50) -- Piedra base
				pc.remove_item("90011", 45) -- Tronco
				pc.remove_item("90012", 40) -- Contrachapado
				say(string.format("Tama�o actual: %d (m�x. 3)", 3)) --1595
			else
				if pc.get_gold() < 50000000 then
					say("La cuenta de la guild no tiene suficientes Yang.[ENTER]Por favor, agrega m�s Yang e int�ntalo de nuevo.") --1590
				elseif pc.count_item(90010) < 50 or pc.count_item(90012) < 40 or pc.count_item(90011) < 45 then
					say("No tienes los elementos necesarios.") --1590
				else
					say("Error20")
				end
			end
		end

	end
end
