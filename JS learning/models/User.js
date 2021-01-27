const mongoose = require('mongoose');

const userSchema = mongoose.Schema({
    name:{
        type: String,
        maxlength: 50
    },
    email: {
        type: String,
        trim: true, //! 스페이스를 없애주는 효과
        unique: 1 //! 똑같은거 못쓴다.
    },
    password: {
        type: String,
        minlength: 5
    },
    lastname: {
        type: String,
        maxlength: 50
    },
    role: {
        type: Number,
        default: 0 //! 기본값은 0이고 관리자, 일반 등등해서 number로 지정가능
    },
    image: String,
    token: {
        type: String
    },
    tokenExp:{
        type: Number
    }
})

const User = mongoose.model('User', userSchema) //! 스키마를 모델로 감싼다.

module.exports = { User }