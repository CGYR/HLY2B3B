<template>
    <!-- 导航栏组件 -->
    <div>
      <el-menu
        :default-active="activeIndex2"
        class="el-menu-demo"
        mode="horizontal"
        @select="handleSelect"
        background-color="#545c64"
        text-color="#fff"
        active-text-color="#ffd04b">
        <el-menu-item index="1">
        <span><img src="./../../static/img/tutu2.png" style="height:60px;"></span>
          <span>软工实验</span>
        </el-menu-item>
        <el-menu-item index="2">

        </el-menu-item>
        <span style="position: absolute;right:190px;">
        <el-menu-item index="3" >实验一</el-menu-item>
        </span>
        <span style="position: absolute;right:100px;">
        <el-menu-item index="4" >实验二</el-menu-item>
        </span>
        <span style="position: absolute;right:10px;">
        <el-menu-item index="5" >关于小组</el-menu-item>
        </span>
      </el-menu>
    </div>
</template>

<script>
    export default {
      data() {
        return {
          activeIndex: '1',
          activeIndex2: '1',
          subject:'',

        };
      },
      methods: {
        handleSelect(key, keyPath) {
          console.log(key, keyPath);
        }
      }
    }
</script>

<style scoped>

</style>
