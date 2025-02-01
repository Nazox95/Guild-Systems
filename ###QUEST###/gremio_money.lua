quest guild_money_in_out begin
	state start begin
		when 11000.chat."Cuenta del gremio: Ingresar" or 11002.chat."Cuenta del gremio: Ingresar" or 11004.chat."Cuenta del gremio: Ingresar" with pc.hasguild() begin --1602
			if not is_guild_money_enabled() then
				say("Esta opción está desactivada de momento.")
				return
			end

			addimage(20, 12, "guildmoney.tga")
			say("")
			say("")
			say("")
			say(string.format("Balance de la cuenta del gremio: %d Yang", guild.get_money0())) --1609
			say("Introduce la cantidad de Yang que quieres[ENTER]ingresar en la cuenta del gremio:") --1604

			local money_in = tonumber(input())
			if ( (money_in == nil) or (money_in < 1) or (money_in > 1999999999) or (math.mod(money_in, 1) ~= 0) ) then
				addimage(20, 12, "guildmoney.tga")
				say("")
				say("")
				say("")
				say("¡No has introducido una cantidad!") --1610
				return
			end
			addimage(20, 12, "guildmoney.tga")
			say("")
			say("")
			say("")
			say(string.format("Comprueba si la cantidad es correcta: %d Yang", money_in)) --1608

			if select("Sí	", "No") == 2 then return end

			if pc.get_gold() < money_in then
				addimage(20, 12, "guildmoney.tga")
				say("")
				say("")
				say("")
				say("No hay suficiente Yang para realizar el ingreso.") --1606
				return
			end

			guild.money_in(money_in)
		end

		when 11000.chat."Cuenta del gremio: Sacar" or 11002.chat."Cuenta del gremio: Sacar" or 11004.chat."Cuenta del gremio: Sacar" with pc.hasguild() begin --1603
			if not is_guild_money_enabled() then
				say("Esta opción está desactivada de momento.")
				return
			end

			addimage(20, 12, "guildmoney.tga")
			say("")
			say("")
			say("")
			say(string.format("Balance de la cuenta del gremio: %d Yang", guild.get_money0())) --1609
			say("Introduce la cantidad de Yang que quieres sacar[ENTER]de la cuenta del gremio:") --1605

			local money_out = tonumber(input())
			if ( (money_out == nil) or (money_out < 1) or (money_out > 1999999999) or (math.mod(money_out, 1) ~= 0) ) then
				say("¡No has introducido una cantidad!") --1610
				return
			end

			say(string.format("Comprueba si la cantidad es correcta: %d Yang", money_out)) --1608

			if select("Sí	", "No") == 2 then return end

			if guild.get_money0() < money_out then
				addimage(20, 12, "guildmoney.tga")
				say("")
				say("")
				say("")
				say("No hay suficiente Yang disponible para sacar de[ENTER]la cuenta del gremio.") --1607
				return
			end

			guild.money_out(money_out)
		end

	end
end
