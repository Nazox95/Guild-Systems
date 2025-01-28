https://youtu.be/W4GSReO02ck

You can check last_play using this query:

SELECT player.id, player.account_id, account.last_play FROM player.player INNER JOIN account.account ON player.account_id = account.id WHERE DATE_SUB(NOW(), INTERVAL 1 MONTH) > account.last_play;

Actually i'm working in create a quest for gms to clean lands but i'm busy with other systems, when i can update this you can see.

Enjoy the system :)
