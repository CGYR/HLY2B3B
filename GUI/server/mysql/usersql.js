var UserSQL = {
    //insert:'INSERT INTO User(uid,userName) VALUES(?,?)',
    selectOne:'SELECT * FROM User WHERE name = ? ',
    queryPart:'SELECT * FROM User LIMIT ?,?',
    queryNum:'SELECT COUNT(*) FROM User',
    insertAll:'INSERT INTO User(name,phone,password) VALUES(?,?,?)',
    deleteOne:'DELETE FROM User WHERE name = ?',
    updateOne:'UPDATE User SET name= ? , phone = ? WHERE name = ?',
};
module.exports = UserSQL;