/* fuser: user, process, file, superblock, and opened_file */
SELECT DISTINCT `superblock`.`dev` AS `FS`, `process`.`pid` AS `process`, 
	`user`.`name` AS `user`, COUNT(`file`.`file_id`) AS `Total opened`
FROM (`user` INNER JOIN `process` ON (`user`.`uid` = `process`.`uid`)) 
	INNER JOIN 
	((`file` INNER JOIN `superblock` ON `file`.`dev` = `superblock`.`dev`) 
	INNER JOIN `opened_file` ON `file`.`file_id` = `opened_file`.`file_id`) 
	ON `process`.`pid` = `opened_file`.`pid`
GROUP BY `superblock`.`dev`, `process`.`pid`
ORDER BY `superblock`.`dev` ASC, BINARY(`user`.`name`) DESC;

