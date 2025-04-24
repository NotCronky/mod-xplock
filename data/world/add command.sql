-- Add the .xplock command to the world DB so it's visible in .help
DELETE FROM `command` WHERE `name` = 'xplock';
INSERT INTO `command` (`name`, `security`, `help`) VALUES
('xplock', 0, 'Toggle XP gain on or off for your character.');
