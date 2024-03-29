----------------------------------
-- Crazy House 1FB (north)      --
-- TODO: MAP TERMINEE, A TESTER --
----------------------------------

guichet43_sprite = sol.map.npc_get_sprite("GC43S")

-- Guichet 41 -------------------------------------------------
function guichet_41()
	if sol.game.savegame_get_integer(1410) == 3 then
		sol.map.dialog_start("crazy_house.guichet_41_ech_eq_3")
		sol.game.savegame_set_integer(1410, 4)
	else
		sol.map.dialog_start("crazy_house.guichet_41_ech_ne_3")
	end
end

-- Guichet 43 -------------------------------------------------
function guichet_43()
	sol.map.dialog_start("crazy_house.guichet_43")
end

-- Guichet 45 -------------------------------------------------
function guichet_45()
	if sol.game.savegame_get_integer(1410) == 3 then
		sol.map.dialog_start("crazy_house.guichet_45_ech_eq_3")
	else
		sol.map.dialog_start("crazy_house.guichet_45_ech_ne_3")
	end
	-- Incrémentation branche 1412
	branche1412 = sol.game.savegame_get_integer(1412)
	if branche1412 > 0 and branche1412 <= 3 then
		sol.game.savegame_set_integer(1412, 4)
	end
end

-- Guichet 47 -------------------------------------------------
function guichet_47()
	if sol.game.savegame_get_integer(1410) == 3 then
		sol.map.dialog_start("crazy_house.guichet_47_ech_eq_3")
	else
		sol.map.dialog_start("crazy_house.guichet_47_ech_ne_3")
	end
end

-- Guichet 49 -------------------------------------------------
function guichet_49()
	sol.map.dialog_start("crazy_house.guichet_49")
end

function event_hero_interaction(entity_name)
	if entity_name == "mario_message_2" then
-- Tableau de mario qui parle ---------------------------------
		sol.main.play_sound("sm64_heehee")
	elseif entity_name == "GC41" then
		guichet_41()
	elseif entity_name == "GC43" then
		guichet_43()
	elseif entity_name == "GC45" then
		guichet_45()
	elseif entity_name == "GC47" then
		guichet_47()
	elseif entity_name == "GC49" then
		guichet_49()
	end
end

function event_dialog_finished(first_message_id, answer)
	if first_message_id == "crazy_house.guichet_43" then
		-- Piplette (guichet 43) qui se tourne vers Link, énervée
		sol.main.sprite_set_direction(guichet43_sprite, 3)
		sol.map.dialog_start("crazy_house.guichet_43n")
	elseif first_message_id == "crazy_house.guichet_43n" then
		-- Piplette reprend sa conversation
		sol.main.sprite_set_direction(guichet43_sprite, 2)
		sol.map.dialog_start("crazy_house.guichet_43f")
	elseif first_message_id == "crazy_house.guichet_45_ech_ne_3" then
		if answer == 0 then
			if sol.game.get_item_amount("cuillere_counter") >= 1 then
				sol.map.dialog_start("crazy_house.guichet_45_ech_ok")
			else
				sol.main.play_sound("wrong")
				sol.map.dialog_start("crazy_house.guichet_45_ech_un")
			end		
		end
	elseif first_message_id == "crazy_house.guichet_45_ech_ok" then
		sol.map.treasure_give("sac_olive", 1, -1)
		sol.game.remove_item_amount("cuillere_counter", 1)
	end
end

