CREATE TABLE `menus_days` (
`id` INT NOT NULL AUTO_INCREMENT,
`menu_id` INT NOT NULL,
`day` INT NULL,
`date_from` DATE NULL,
`parent_id` INT NULL DEFAULT NULL,
PRIMARY KEY (`id`),
FOREIGN KEY (`menu_id`) REFERENCES `menus` (`id`) ON UPDATE CASCADE ON DELETE CASCADE
)
COLLATE='utf8_general_ci'
;

ALTER TABLE `menus_days_mealslists`
ADD COLUMN `day_id` INT NULL DEFAULT NULL AFTER `day`,
ADD FOREIGN KEY (`day_id`) REFERENCES `menus_days` (`id`);


DELIMITER //

CREATE PROCEDURE menus_days_filling ()
BEGIN
DECLARE done BOOLEAN;
DECLARE cday, cmenu_id INT;
DECLARE days_cur CURSOR FOR
SELECT
`day`,
`menu_id`
FROM menus_days_mealslists
GROUP BY day, menu_id
ORDER BY menu_id;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

OPEN days_cur;

read_loop: LOOP
   FETCH days_cur INTO cday, cmenu_id;
   IF done THEN
     LEAVE read_loop;
   END IF;
   
   INSERT INTO menus_days (`menu_id`, `day`) VALUES (cmenu_id, cday);
   UPDATE menus_days_mealslists SET `day_id` = (SELECT `id` FROM menus_days WHERE `menu_id` = cmenu_id AND `day` = cday LIMIT 1) WHERE menu_id = cmenu_id AND `day` = cday;
 END LOOP;
 
 CLOSE days_cur;
END//

DELIMITER ;

CALL menus_days_filling();
DROP PROCEDURE IF EXISTS `menus_days_filling`;


ALTER TABLE `menus_days_mealslists`
CHANGE COLUMN `day_id` `day_id` INT(11) NOT NULL AFTER `day`;

ALTER TABLE `menus_days_mealslists`
DROP COLUMN `day`,
DROP FOREIGN KEY `menus_days_mealslists_ibfk_1`,
DROP COLUMN `menu_id`;
