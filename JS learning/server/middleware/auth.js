const { User } = require("../models/User");

let auth = (req, res, next) => {

    //! ����ó���� �Ѵ�.~

    //! Ŭ���̾�Ʈ ��Ű���� ��ū�� �����´�.
    let token = req.cookies.x_auth;


    //! ��ū�� �޾Ƽ� ������ ã�´�.
    User.findByToken(token, (err,user) => {
        if(err) throw err;
        if(!user) return res.json({isAuth: false, error: true})
        
        req.token = token;
        req.user = user;
        next()
    })


    //! ������ ������ ����

    //! ������ ������ ����X

}

module.exports = { auth };